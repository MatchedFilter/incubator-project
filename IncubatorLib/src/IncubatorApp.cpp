#include "Incubator/IncubatorApp.h"

#include "TimeUtils/TimerManager.h"
#include "bsp_config.h"

#include <cstring>
#include <stddef.h>

namespace Incubator
{

const uint8_t RESET_CMD[]         = "reset";
constexpr uint16_t RESET_CMD_SIZE = sizeof(RESET_CMD) - 1U;
const uint8_t ALIVE_CMD[]         = "alive";
constexpr uint16_t ALIVE_CMD_SIZE = sizeof(ALIVE_CMD) - 1U;

void IncubatorApp::Initialize()
{
  m_Timer             = TimeUtils::TimerManager::CreateMillisecondTimer();
  m_HeartbeatUsbTimer = TimeUtils::TimerManager::CreateMillisecondTimer();
  m_Timer->SetDuration(50U);
  m_HeartbeatUsbTimer->SetDuration(5000U);
}

void IncubatorApp::Run()
{
  if (m_Timer->IsFinished())
  {
    bsp_internal_led_toggle();
    m_Timer->Start();
  }
  if (m_HeartbeatUsbTimer->IsFinished())
  {
    bsp_usb_send_data(ALIVE_CMD, ALIVE_CMD_SIZE);
    m_HeartbeatUsbTimer->Start();
  }

  if (bsp_is_usb_data_ready())
  {
    uint32_t usbDataLength = 0U;
    const uint8_t *usbData = bsp_get_usb_data(&usbDataLength);
    if (usbData != NULL)
    {
      if (std::memcmp(usbData, RESET_CMD, RESET_CMD_SIZE) == 0)
      {
        // bsp_reset();
      }

      for (uint32_t i = 0U; i < 3; i++)
      {
        bsp_internal_led_turn_on();
        bsp_delay_in_millisecond(5000);
        bsp_internal_led_turn_off();
        bsp_delay_in_millisecond(5000);
      }
    }
  }
}
} // namespace Incubator
