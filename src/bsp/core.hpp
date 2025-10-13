/**
 * @file core.hpp
 * @brief contains close to cpu peripheral controls to startup controller
 */

#pragma once

namespace bsp
{
class Core
{
  public:
    Core();

    ~Core();

  private:
    void clock_config();
};
} // namespace bsp
