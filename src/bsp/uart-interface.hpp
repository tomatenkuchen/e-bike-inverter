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

    /**
     * @brief read character stream from uart
     *
     * @param read_data data from uart. provide the container where the data should be stored. make sure it exists until
     *                  the reception is complete
     * @return true     ok
     * @return false    error
     */
    bool read(std::span<uint8_t> read_data);

    /**
     * @brief send character stream to uart
     *
     * @param data   data to send. provide the container with the data and make sure it exists until the transmission is
     *               complete
     * @return true  ok
     * @return false error
     */
    bool write(std::span<uint8_t const> data);

    /**
     * @brief interrupt handler for uart. Should be called on tx complete interrupt
     */
    void tx_interrupt_hander();

    /**
     * @brief interrupt handler for uart. Should be called on rx complete interrupt
     */
    void rx_interrupt_hander();

  private:
    bool rx_busy = false;
    bool tx_busy = false;
};

} // namespace bsp