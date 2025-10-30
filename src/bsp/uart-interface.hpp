/**
 * @file uart-interface.hpp
 * @brief uart output
 */

#pragma once

#include <array>
#include <cstdint>
#include <span>

namespace bsp
{

class Uart
{
  public:
    Uart();
    ~Uart();
    bool read(std::span<uint8_t> read_data);
    bool write(std::span<uint8_t const> data);
};

} // namespace bsp