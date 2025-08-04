#include <vector>
#include <memory>

class alloc {
public:
    using block_t = int8_t;

    static std::pair<std::shared_ptr<block_t>, uint8_t> allocate() {
        if (bit_index == 8) {
            bit_index = 0;
            blocks.push_back(std::make_shared<block_t>(0));
        }
        auto block = blocks.back();
        uint8_t pos = bit_index++;
        return {block, pos};
    }
private:
    static inline std::vector<std::shared_ptr<block_t>> blocks;
    static inline uint8_t bit_index = 8;
};

class byteB {
public:
    byteB() {
        std::tie(block, bit_pos) = alloc::allocate();
    }
    byteB(bool val) : byteB() {
        *this = val;
    }
    byteB& operator=(bool val) {
        if (val)
            *block |= (1 << bit_pos);
        else
            *block &= ~(1 << bit_pos);
        return *this;
    }
    operator bool() const {
        return (*block >> bit_pos) & 1;
    }
private:
    std::shared_ptr<alloc::block_t> block;
    uint8_t bit_pos;
};
