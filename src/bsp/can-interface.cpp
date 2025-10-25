#include "can-interface.hpp"

namespace bsp
{

Can::Can()
{
}

std::span<uint8_t const> Can::read(std::size_t num_of_bytes)
{
}

void Can::write(std::span<uint8_t const> data)
{
}

} // namespace bsp