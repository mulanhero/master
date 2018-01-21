#include <atomic>
#include <iostream>

class Block {
    public:
        static int64_t get_new_id() {
            static std::atomic<int64_t> block_id(0);
            return ++block_id;
        }

        Block(int _age) : age(_age) {
        }


        int get_age() const {
            return age;
        }
   private:
        int age;
};

int main() {
    Block b1(10);
    std::cout << Block::get_new_id() << ":" << b1.get_age() << std::endl;
    Block b2(22);
    std::cout << Block::get_new_id() << ":" << b2.get_age() << std::endl;
    return 0;
}
