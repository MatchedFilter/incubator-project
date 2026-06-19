#ifndef INCUBATOR_LCD2004_H
#define INCUBATOR_LCD2004_H

#include <bsp_config.h>
#include <cstdint>
namespace Incubator
{
class Lcd2004
{
public:
  Lcd2004() = delete;

  static auto Initialize(void) -> void;
  static auto Run(void) -> void;

  template <uint8_t N>
  static auto Print(const char (&chrArr)[N], uint8_t size = N, uint8_t offset = 0U) -> void;

private:
};

template <uint8_t N>
auto Lcd2004::Print(const char (&chrArr)[N], const uint8_t size, const uint8_t offset) -> void
{
  for (uint8_t i = offset; i < size; i++)
  {
    if (chrArr[i] >= ' ')
    {
      bsp_lcd_20x4_send_data(chrArr[i]);
    }
  }
}

} // namespace Incubator
#endif // INCUBATOR_LCD2004_H
