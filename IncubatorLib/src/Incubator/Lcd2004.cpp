#include "Incubator/Lcd2004.h"

#include "bsp_config.h"

namespace Incubator
{

auto Lcd2004::Print(const uint8_t specialChar) const -> void
{
  bsp_lcd_20x4_send_data(specialChar);
}

auto Lcd2004::MoveCursor(const uint8_t lineNumber, const uint8_t column) const -> void
{
  const uint8_t columnPart = static_cast<uint8_t>(column & static_cast<uint8_t>(0x0FU));
  switch (lineNumber)
  {
    case 0U:
    {
      const uint8_t command = 0x80U + columnPart;
      bsp_lcd_20x4_send_command(command);
      break;
    }

    case 1U:
    {
      const uint8_t command = 0xC0U + columnPart;
      bsp_lcd_20x4_send_command(command);
      break;
    }

    case 2U:
    {
      bsp_lcd_20x4_send_command(0x8FU);
      const uint8_t restShiftSize = 5U + column;
      for (uint8_t i = 0U; i < restShiftSize; i++)
      {
        constexpr uint8_t SET_CURSOR_TO_NEXT_CHAR_COMMAND = 0x14U;
        bsp_lcd_20x4_send_command(SET_CURSOR_TO_NEXT_CHAR_COMMAND);
      }
      break;
    }

    case 3U:
    {
      bsp_lcd_20x4_send_command(0xCFU);
      const uint8_t restShiftSize = 5U + column;
      for (uint8_t i = 0U; i < restShiftSize; i++)
      {
        constexpr uint8_t SET_CURSOR_TO_NEXT_CHAR_COMMAND = 0x14U;
        bsp_lcd_20x4_send_command(SET_CURSOR_TO_NEXT_CHAR_COMMAND);
      }
      break;
    }

    default:
      break;
  }
}

auto Lcd2004::Clear(void) const -> void
{
  static constexpr uint8_t CLEAR_SCREEN_COMMAND = 0x01U;
  bsp_lcd_20x4_send_command(CLEAR_SCREEN_COMMAND);
}

auto Lcd2004::Run(void) -> void
{
  bsp_lcd_20x4_process_run();
}

} // namespace Incubator
