/**
 * @file double_dict.h
 *
 **/
#ifndef DOUBLE_DICT_H
#define DOUBLE_DICT_H

#include "common.h"
using namespace std;
#include "mpi.h"

#pragma pack (2)
/**
 * @brief :weight_count_entry_t
 *
 * @param
 * @return
**/
class weight_count_entry_t {
public:
    /** 主键 **/
    double primary_key;
    /** count **/
    uint64_t count;
    /**
     * @brief 小于
     **/
    inline const bool operator <(const weight_count_entry_t& source) const {
        return primary_key < source.primary_key;
    }
    /**
     * @brief 合并
     **/
    inline weight_count_entry_t& operator += (const weight_count_entry_t& source) {
        this->count += source.count;
        return *this;
    }
};

#pragma pack (8)
namespace double_dict {
/**< >**/
template<typename T_advanced_entry_t>
class sorted_distributed_dict_t {
private:
    typedef T_advanced_entry_t advanced_entry_t; ///<定义

public:

    advanced_entry_t* _entries; ///<_entries
    int64_t* _load_split;///<_load_split

    uint64_t _entry_size;///<_entry_size
    int _rank;///<_rank
    int _size;///<_size

    bool splited;///<是否空间上复用其他对象而在析构时无需释放 by Xuruiwen
    /**
     * @brief 构造函数
     **/
    sorted_distributed_dict_t(advanced_entry_t* _entries, int64_t entry_size,
            int rank, int size) {
        this->_entries = _entries;
        this->_entry_size = entry_size;
        this->_rank = rank;
        this->_size = size;
        _load_split = NULL;
        splited = false;
    }
    /**
     * @brief 析构函数
     **/
    ~sorted_distributed_dict_t() {
        if (!splited) {
            DELETES(_entries);
        }
        if (_load_split) {
            DELETES(_load_split);
            _load_split = NULL;
        }
    }

    /**
     * @brief:  内部排序
     *
     * @param
     * @return
    **/
    int sort() {
        if (_entry_size) {
            std::sort(_entries, _entries + _entry_size);
        }
        return uniq();
    }

    /**
     * @brief:  去重
     *
     * @param
     * @return
    **/
    int uniq() {
        if (_entry_size == 0) {
            return 0;
        }
        uint64_t i;
        uint64_t new_size = 0;
        for (i = 1; i < _entry_size; i++) {
            if (_entries[new_size] < _entries[i]) {
                _entries[++new_size] = _entries[i];
            } else {
                _entries[new_size] += _entries[i];
            }
        }
        _entry_size = new_size + 1;
        return 0;
    }

    /**
     * @brief:  计算当前节点大等于lower_bound的特征签名个数
     *
     * @param
     * @return
    **/
    int64_t count_local_element_greater_than(double lower_bound) {
        int64_t left = -1;
        int64_t right = _entry_size;

        while (left + 1 < right) {
            int64_t mid = (left + right) >> 1;
            if ((_entries + mid)->primary_key >= lower_bound) {
                right = mid;
            } else {
                left = mid;
            }
        }

        return _entry_size - right;
    }

    /**
     * @brief:  计算所有节点大等于lower_bound的特征签名个数（多任务）
     *
     * @param
     * @return
    **/
    int count_global_element_greater_than(double* lower_bound,
            int64_t* result, int count) {
        if (!lower_bound || !result) {
            FATAL(" lower_bound or result is NULL");
            return -1;
        }
        int64_t* local_count = new(std::nothrow) int64_t[count];
        if (!local_count) {
            FATAL("newmem for local_count fail");
            return -1;
        }
        for (int i = 0; i < count; i++) {
            local_count[i] = count_local_element_greater_than(lower_bound[i]);
        }

        int ret = 0;
        if (0 != MPI_Allreduce(local_count, result, count, MPI_LONG_LONG_INT,
                MPI_SUM, MPI_COMM_WORLD)) {
            FATAL("call MPI_Allreduce() fail");
            ret = -1;
        }

        DELETES(local_count);
        return ret;
    }

    /**
     * @brief: 负载均衡继计算（网络传输均衡）
     *
     * @param
     * @return
    **/
    int load_balance() {
        if (_load_split) {
            DELETES(_load_split);
        }
        _load_split = new(std::nothrow) int64_t[_size + 1];
        if (_load_split == NULL) {
            FATAL("newmem for _load_split fail");
            return -1;
        }
        int64_t* buffer = new(std::nothrow) int64_t[_size * 7];
        if (buffer == NULL) {
            FATAL("newmem for buffer fail");
            return -1;
        }
        int ret = 0;
        int64_t* cover_size = buffer;
        int64_t* left_size = buffer + _size;
        int64_t* right_size = buffer + _size * 2;
        int64_t* mid_size = buffer + _size * 3;
        double* left = (double*)(buffer + _size * 4);
        double* right = (double*)(buffer + _size * 5);
        double* mid = (double*)(buffer + _size * 6);

        double max = 0;
        double min = 0;
        int64_t count = 0;
        double lower;
        int64_t total_size;
        for (uint64_t i = 0; i < _entry_size; i++) {
            if (count == 0 || _entries[i].primary_key > max) {
                max = _entries[i].primary_key;
            }
            if (count == 0 || _entries[i].primary_key < min) {
                min = _entries[i].primary_key;
            }
            count++;
        }

        double* max_all = left;
        double* min_all = right;
        if (MPI_Allgather(&(max), 1,
                MPI_DOUBLE, max_all, 1, MPI_DOUBLE,
                MPI_COMM_WORLD) != 0) {
            FATAL("call MPI_Allgather() fail");
            return -1;
        }
        if (MPI_Allgather(&(min), 1,
                MPI_DOUBLE, min_all, 1, MPI_DOUBLE,
                MPI_COMM_WORLD) != 0) {
            FATAL("call MPI_Allgather() fail");
            return -1;
        }
        if (MPI_Allgather(&(count), 1,
                MPI_LONG_LONG, cover_size, 1, MPI_LONG_LONG,
                MPI_COMM_WORLD) != 0) {
            FATAL("call MPI_Allgather() fail");
            return -1;
        }

        max = 0;
        min = 0;
        count = 0;
        for (int i = 0; i < _size; i++) {
            if (cover_size[i] > 0) {
                if (count == 0 || max_all[i] > max) {
                    max = max_all[i];
                }
                if (count == 0 || min_all[i] < min) {
                    min = min_all[i];
                }
                count++;
            }
        }

        if (count == 0) {
            for (int i = 0; i < _size + 1; i++) {
                _load_split[i] = 0;
            }
            ret = 0;
            goto end_point;
        }

        if (min - 1 < min && max + 1 > max) {
            min = min - 1;
            max = max + 1;
        } else {
            FATAL("error,min=" << min << "max=" << max);
            return -1;
        }

        lower = min;
        total_size = 0;
        if (count_global_element_greater_than(&lower, &total_size, 1) != 0) {
            FATAL("call count_global_element_greater_than() fail");
            return -1;
        }

        for (int i = 0; i < _size; i++) {
            cover_size[i] = total_size - i * total_size / _size;
            left[i] = min;
            right[i] = max;
            mid[i] = (min + max) / 2;
        }
        if ((ret = count_global_element_greater_than(left, left_size, _size)) < 0) {
            goto end_point;
        }
        if ((ret = count_global_element_greater_than(right, right_size, _size)) < 0) {
            goto end_point;
        }
        while (true) {
            int k = 0;
            for (int i = 0; i < _size; i++) {
                if (left_size[i] == right_size[i]) {
                    k++;
                } else {
                    /**<  mid = (left + right + 1) / 2 , left < right >**/
                    mid[i] = (left[i] + right[i]) / 2;
                    if (left[i] == mid[i] || right[i] == mid[i]) {
                        k++;
                    }
                }
            }
            if (k == _size) {
                break;
            }
            if ((ret = count_global_element_greater_than(mid, mid_size, _size)) < 0) {
                break;
            }
            for (int i = 0; i < _size; i++) {
                if (mid_size[i] < cover_size[i]) {
                    right[i] = mid[i];
                    right_size[i] = mid_size[i];
                } else {
                    left[i] = mid[i];
                    left_size[i] = mid_size[i];
                }
            }
        }
        if (ret == 0) {
            right[0] = min;
            for (int i = 0; i < _size; i++) {
                _load_split[i] = _entry_size - count_local_element_greater_than(right[i]);
            }
            _load_split[0] = 0;
            _load_split[_size] = _entry_size;
        }
end_point:
        DELETES(buffer);
        return ret;
    }

    /**
     * @brief: 计算两个整数区间的交集
     *
     * @param
     * @return
    **/
    void common_range(uint64_t& lower, uint64_t& upper, uint64_t lower_0,
            uint64_t upper_0, uint64_t lower_1, uint64_t upper_1) {
        lower = lower_0;
        if (lower < lower_1) {
            lower = lower_1;
        }
        upper = upper_0;
        if (upper > upper_1) {
            upper = upper_1;
        }
    }

    /**
     * @brief: 负载均衡继计算（存储大小均衡）
     *
     * @param
     * @return
    **/
    sorted_distributed_dict_t* build_store_balance_dict(const int balance_opt = 0) {
        if (_load_split) {
            DELETES(_load_split);
            _load_split = NULL;
        }
        _load_split = new(std::nothrow) int64_t[_size + 1];
        if (_load_split == NULL) {
            FATAL("newmem for _load_split fail");
            return NULL;
        }

        if (MPI_Allgather(&_entry_size, 1, MPI_LONG_LONG_INT, _load_split, 1,
                MPI_LONG_LONG_INT, MPI_COMM_WORLD) != 0) {
            FATAL("call MPI_Allgather() fail");
            return NULL;
        }

        int64_t total_feature_num = 0;

        for (int i = 0; i < _size; i++) {
            total_feature_num += _load_split[i];
        }
        _load_split[_size] = total_feature_num;
        for (int i = _size - 1; i >= 0; i--) {
            _load_split[i] = _load_split[i + 1] - _load_split[i];
        }

        int64_t balance_dict_size = 0;
        if (balance_opt != 0 && balance_opt != 1) {
            FATAL("balance_opt!=0 && balance_opt!=1");
            return NULL;
        }

        if (0 == balance_opt) { //对于feature >= node num的情况
            int64_t num_features_per_node = total_feature_num / _size + 1;
            int64_t balance_dict_offset = _rank * num_features_per_node;
            balance_dict_size = num_features_per_node;
            int64_t diff = balance_dict_offset + balance_dict_size
                           - total_feature_num;
            if (diff > 0) {
                balance_dict_size -= diff;
            }
        } else { //对于feature < node num的情况
            int64_t num_features_per_node = total_feature_num / _size ;
            int64_t features_int = num_features_per_node * _size;;
            int64_t diff = total_feature_num - features_int;
            if (_rank < diff) {
                balance_dict_size = num_features_per_node + 1;
            } else {
                balance_dict_size = num_features_per_node;
            }
        }

        if (balance_dict_size <= 0) {
            FATAL("balance_dict_size<=0 [" << balance_dict_size << "]"); //不允许节点无元素
            return NULL;
        }

        advanced_entry_t* balance_entry =
            new(std::nothrow) advanced_entry_t[balance_dict_size];
        if (!balance_entry) {
            FATAL("newmem for balance_entry fail");
            return NULL;
        }

        sorted_distributed_dict_t* balance_dict =
            new(std::nothrow) sorted_distributed_dict_t(balance_entry,
                    balance_dict_size, _rank, _size);

        balance_dict->_load_split = new(std::nothrow) int64_t[_size + 1];
        if (balance_dict->_load_split == NULL) {
            FATAL("newmem for balance_dict _load_split fail");
            return NULL;
        }

        if (MPI_Allgather(&balance_dict_size, 1, MPI_LONG_LONG_INT,
                balance_dict->_load_split, 1, MPI_LONG_LONG_INT, MPI_COMM_WORLD)
                != 0) {
            FATAL("call balance_dict MPI_Allgather() fail");
            return NULL;
        }
        balance_dict->_load_split[_size] = total_feature_num;
        for (int i = _size - 1; i >= 0; i--) {
            balance_dict->_load_split[i] = balance_dict->_load_split[i + 1]
                                           - balance_dict->_load_split[i];
        }

        MPI_Request mpi_request[4096];
        MPI_Status status;

        uint64_t max_send_count = G_MPI_MAX_SEND_SIZE / sizeof(advanced_entry_t);

        for (int i = 0; i < _size; i++) {
            int send_to = (_rank + i) % _size;
            int recv_from = (_rank + _size - i) % _size;
            uint64_t send_lower;
            uint64_t send_upper;
            uint64_t recv_lower;
            uint64_t recv_upper;
            common_range(send_lower, send_upper, _load_split[_rank],
                    _load_split[_rank + 1], balance_dict->_load_split[send_to],
                    balance_dict->_load_split[send_to + 1]);
            common_range(recv_lower, recv_upper, _load_split[recv_from],
                    _load_split[recv_from + 1],
                    balance_dict->_load_split[_rank],
                    balance_dict->_load_split[_rank + 1]);

            int tag = 0;
            if (send_lower < send_upper) {
                advanced_entry_t* send = _entries + send_lower
                                         - _load_split[_rank];
                uint64_t total = send_upper - send_lower;
                while (total) {
                    uint64_t size = total;
                    if (size > max_send_count) {
                        size = max_send_count;
                    }
                    tag++;
                    if (MPI_Isend(send, size * sizeof(advanced_entry_t), MPI_BYTE, send_to, /**<modified by pengdan>**/
                            tag, MPI_COMM_WORLD, &mpi_request[tag]) != 0) {
                        FATAL("call MPI_Isend() fail");
                        return NULL;
                    }
                    send += size;
                    total -= size;
                }
            }

            if (recv_lower < recv_upper) {
                advanced_entry_t* recv = balance_dict->_entries + recv_lower
                                         - balance_dict->_load_split[_rank];
                uint64_t total = recv_upper - recv_lower;
                int tag = 1;
                while (total) {
                    uint64_t size = total;
                    if (size > max_send_count) {
                        size = max_send_count;
                    }
                    if (MPI_Recv(recv, size * sizeof(advanced_entry_t), MPI_BYTE, recv_from,
                            tag++, MPI_COMM_WORLD, &status) != 0
                            || status.MPI_ERROR != MPI_SUCCESS) {
                        FATAL("call MPI_Recv() fail");
                        return NULL;
                    }
                    recv += size;
                    total -= size;
                }
            }

            if (send_lower < send_upper) {
                if (MPI_Wait(&mpi_request[tag], &status) != 0
                        || status.MPI_ERROR != MPI_SUCCESS) {
                    FATAL("call MPI_Wait() fail");
                    return NULL;
                }
            }
        }

        return balance_dict;
    }

    /**
     * @brief: 建立分布式字典
     *
     * @param
     * @return
    **/
    sorted_distributed_dict_t* build_global_dict() {

        if (_load_split) {
            DELETES(_load_split);
            _load_split = NULL;
        }

        if (load_balance() < 0) {
            FATAL("call load_balance() fail");
            return NULL;
        }

        int64_t* send_size = new(std::nothrow) int64_t[_size + 1];
        int64_t* receive_size = new(std::nothrow) int64_t[_size + 1];
        int64_t* receive_offset = new(std::nothrow) int64_t[_size + 1];

        if (send_size == NULL || receive_size == NULL || receive_offset == NULL) {
            FATAL("newmem for send_size or receive_size or receive_offset fail");
            return NULL;
        }

        int64_t max_send_size = 0;
        for (int i = 0; i < _size; i++) {
            send_size[i] = _load_split[i + 1] - _load_split[i];
            if (max_send_size < send_size[i]) {
                max_send_size = send_size[i];
            }
        }

        if (0 != MPI_Alltoall(send_size, 1, MPI_LONG_LONG_INT, receive_size,
                1, MPI_LONG_LONG_INT, MPI_COMM_WORLD)) {
            FATAL("call MPI_Alltoall() fail");
            return NULL;
        }

        mpi_packed mpi_t;
        if (mpi_t.error) {
            FATAL("mpi_packed init fail");
            return NULL;
        }

        int64_t total_receive_size = 0;
        for (int i = 0; i < _size; i++) {
            int64_t t = mpi_t.init_size(receive_size[i]);
            receive_offset[i] = total_receive_size;
            total_receive_size += t;
        }
        receive_offset[_size] = total_receive_size;

        advanced_entry_t* new_entrys = new(std::nothrow) advanced_entry_t[total_receive_size];
        advanced_entry_t* send_buffer = new(std::nothrow) advanced_entry_t[mpi_t.init_size(max_send_size)];
        if (new_entrys == NULL || send_buffer == NULL) {
            FATAL("newmem for new_entrys or send_buffer fail");
            return NULL;
        }

        for (int i = 0; i < _size; i++) {
            int send_to = (_rank + i) % _size;
            int recv_from = (_rank + _size - i) % _size;

            advanced_entry_t* p = send_buffer;
            for (uint64_t index = _load_split[send_to]; index
                    < _load_split[send_to + 1]; index++) {
                (*p) = _entries[index];
                ++p;
            }

            if (mpi_t.MPI_ISend_and_Recv(send_buffer, send_size[send_to]*sizeof(advanced_entry_t), send_to, i,
                    new_entrys + receive_offset[recv_from], receive_size[recv_from]*sizeof(advanced_entry_t),
                    recv_from, i) != 0) {
                FATAL("call mpi_t.MPI_ISend_and_Recv fail");
                return NULL;
            }
        }

        total_receive_size = 0;
        for (int i = 0; i < _size; i++) {
            for (int64_t j = 0; j < receive_size[i]; j++) {
                new_entrys[total_receive_size] = *(new_entrys + receive_offset[i] + j);
                total_receive_size++;
            }
        }

        DELETES(send_buffer);
        DELETES(send_size);
        DELETES(receive_offset);
        DELETES(receive_size);

        sorted_distributed_dict_t* ret = new(std::nothrow) sorted_distributed_dict_t(new_entrys,
                total_receive_size, _rank, _size);
        if (!ret) {
            FATAL("newmem for sorted_distributed_dict_t fail");
            return NULL;
        }
        ret->sort();

        if (0 != ret->uniq()) {
            FATAL("call ret->uniq() fail");
            return NULL;
        }

        return ret;
    }
    /**
     * @brief 将一个entries的大小置为size，并把剩余的部分生成另一个sorted_distributed_dict_t
     **/
    sorted_distributed_dict_t* split(uint64_t size) {
        uint64_t total_size = _entry_size;
        if (size < 0 || size > total_size) {
            FATAL("size=" << size << ",error");
            return NULL;
        }
        _entry_size = size;

        sorted_distributed_dict_t* ret = new(std::nothrow) sorted_distributed_dict_t(_entries + size,
                total_size - size, _rank, _size);
        if (ret == NULL) {
            FATAL("newmem for sorted_distributed_dict_t fail");
            return NULL;
        }
        ret->splited = true; //析构时无需释放空间
        return ret;
    }
};
}

/**< >**/
typedef double_dict::sorted_distributed_dict_t<weight_count_entry_t> weight_count_dict_t;

#endif
