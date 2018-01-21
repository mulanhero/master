#include<stdio.h>
#include<vector>
#include "mpi.h"
using namespace std;
int cmp(const void*a, const void* b)
{
    uint32_t a0 = *(uint32_t*)a;
    uint32_t b0 = *(uint32_t*)b;
    if(a0 == b0){
        return 0;
    }else {
        return a0-b0;
    }
}
uint32_t count_local_element_greater_than(uint32_t num, uint32_t&size, uint32_t* local_data, uint32_t local_data_num )
{

    uint32_t*  low = lower_bound(local_data, local_data + local_data_num,num);
    size = local_data+local_data_num - low;
//    printf("bigger than %03u is %u\n",num, size);
    return 0;
}
uint32_t count_gloal_element_greater_than(uint32_t* value, uint32_t* total_biger_than_value, uint32_t* local_data, uint32_t local_data_num,uint32_t size_of_data,int rank)
{
    uint32_t* local_bigger_than_value = new uint32_t [size_of_data] ;
    for(uint32_t i=0;i<size_of_data;i++){
        count_local_element_greater_than(value[i],local_bigger_than_value[i],local_data, local_data_num);
    }
    MPI_Allreduce(local_bigger_than_value,total_biger_than_value,size_of_data,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
    delete [] local_bigger_than_value;
}
uint32_t compute_boundary_value_of_every_rank(uint32_t size_of_node, uint32_t* local_data, uint32_t local_data_num, uint32_t total_data_size, int rank, uint32_t* bound_values)
{
    uint32_t *buf = new uint32_t [size_of_node*4];
    uint32_t avg_of_per_rank = (total_data_size+size_of_node-1)/size_of_node;
    uint32_t* mid  = bound_values;
    uint32_t* low  = buf;
    uint32_t* hgh  = buf+size_of_node*1;
    uint32_t* cover_size = buf+size_of_node*2;
    uint32_t* count_size = buf+size_of_node*3;
    for(uint32_t i = 0; i<size_of_node; ++i){
        low[i] = 1;
        hgh[i] = 0xff;
        mid[i] = (low[i]>>1) +(hgh[i]>>1) + ((low[i]|hgh[i])&1);
        cover_size[i] = total_data_size - (total_data_size*i/size_of_node);
    }
    for(uint32_t k=0;k<32;k++){
        count_gloal_element_greater_than(mid,count_size,local_data, local_data_num,size_of_node,rank);
        if(rank == 0){
            printf("k=%d\n",k);
        }
        for(uint32_t i=0;i<size_of_node;i++){
            if(rank == 0 ){
                printf("mid=%u,low=%u,high=%u,count_size=%u,cover_size=%u\n",mid[i],low[i],hgh[i],count_size[i],cover_size[i]);
            }
            if(count_size[i] < cover_size[i] ){//这里表示阈值大了，需要减小
                hgh[i] = mid[i];
                mid[i] = (low[i]>>1) +(hgh[i]>>1) + ((low[i]|hgh[i])&1);
            }else if(count_size[i] > cover_size[i]){
                low[i] = mid[i];
                mid[i] = (low[i]>>1) +(hgh[i]>>1) + ((low[i]|hgh[i])&1);
            }else {
            }
        }
    }
    printf("after cut %u parts:",size_of_node);
    for(int i=0,j=0;i<local_data_num;i++)
    {
        if(j<size_of_node && mid[j] < local_data[i]){
            printf("# ");
            j++;
        }
        printf("%03u   ",local_data[i]);
    }
    printf("\n");
    delete [] buf;


}
uint32_t mpi_sort(uint32_t size_of_node, uint32_t* local_data, uint32_t local_data_num, uint32_t total_data_size, int rank)
{
    uint32_t *mid = new uint32_t [size_of_node];
    uint32_t *buf = new uint32_t [4*(size_of_node+1)];
    compute_boundary_value_of_every_rank(size_of_node,local_data,local_data_num,total_data_size,rank,mid);
    int j = 0;
    uint32_t*  send_to_idx   = buf;//this node send other node idx
    uint32_t*  recv_from_idx = send_to_idx + size_of_node+1;
    uint32_t*  send_to_len   = recv_from_idx + size_of_node+1;
    uint32_t*  recv_from_len = send_to_len  + size_of_node+1;
    for(int i = 0; i<= size_of_node;i++){
        while(j <local_data_num &&  mid[i] > local_data[j] ){
            j++;
        }
        send_to_idx[i] = j;
        //printf("send_to_idx[%d]:%d\n",i,send_to_idx[i]);
    }
    send_to_idx[size_of_node] = local_data_num;
    for(int i=0;i<size_of_node;i++){
        send_to_len[i] = send_to_idx[i+1] - send_to_idx[i];
        //printf("send_to_len[%u]:%u\n",i,send_to_len[i]);
    }
    uint32_t  last_idx =0;
    MPI_Request mpi_request;
    MPI_Status status;
    int tag = 0;
    uint32_t *p = local_data;
    MPI_Alltoall(send_to_len,1,MPI_INT,recv_from_len,1,MPI_INT,MPI_COMM_WORLD);
    recv_from_idx[0] = 0;
    for( int i = 1;i<=size_of_node;i++ ){
        recv_from_idx[i] = recv_from_idx[i-1] + recv_from_len[i-1];
    }
    for( int i = 0;i<size_of_node;i++ ){
        //printf("recv[%u]:%u\n",i,recv_from_len[i]);
        //printf("recv_from_idx[%u]:%u\n",i,recv_from_idx[i]);
    }
    uint32_t *recv_buf = new uint32_t[recv_from_idx[size_of_node]];
    for(int i =0;i<size_of_node;i++){
        int s_to = (rank + i)%size_of_node;
        int s_from = (rank + size_of_node - i)%size_of_node;
        MPI_Isend(local_data + send_to_idx[s_to],send_to_len[s_to],MPI_INT,s_to,tag,MPI_COMM_WORLD,&mpi_request);
        MPI_Irecv(recv_buf +recv_from_idx[s_from],recv_from_len[s_from],MPI_INT,s_from,tag,MPI_COMM_WORLD,&mpi_request);
        MPI_Wait(&mpi_request,&status);
    }
    qsort(recv_from_idx,recv_from_idx[size_of_node],4,cmp);
    for(int i=0;i<recv_from_idx[size_of_node];i++){
       printf("%03u   ",recv_buf[i]);
    }
    return 0;
}
#define N 10
int main(int argc,char**argv)
{
    MPI_Init(&argc, &argv);
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    srand(time(NULL)-rank);
    uint32_t ranks_data[N] = {0};
    printf("ori data :");
    for(uint32_t j=0;j<N;j++){
            uint32_t v = rand()%0xff;
            ranks_data[j] = v;
            printf("%03d   ",v);
    }
    qsort(ranks_data,N,4,cmp);
    printf("\n after sort:");
    for(uint32_t j=0;j<N;j++){
            printf("%03d   ",ranks_data[j]);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    printf("\n");
    mpi_sort(size, ranks_data, N, size*N, rank);
    MPI_Finalize();
}

