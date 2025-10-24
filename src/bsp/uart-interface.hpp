/**
 * @file uart-interface.hpp
 * @brief uart output
 */

#include <array>
#include <span>
#include <cstdint>

namespace bsp
{

class Uart
{
  public:
    Uart();
    std::span<uint8_t const> read(std::size_t num_of_bytes);
    void write(std::span<uint8_t const> data);

    private:
    std::array<uint8_t, 256> tx_buffer;
    std::array<uint8_t, 256> rx_buffer;
};

}