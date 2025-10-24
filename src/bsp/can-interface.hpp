/**
 * @file can-interface.hpp
 * @brief can com
 */

#include <array>
#include <span>
#include <cstdint>

namespace bsp
{

class Can
{
  public:
    Can();
    std::span<uint8_t const> read(std::size_t num_of_bytes);
    void write(std::span<uint8_t const> data);

    private:
    std::array<uint8_t, 256> tx_buffer;
    std::array<uint8_t, 256> rx_buffer;
};

}