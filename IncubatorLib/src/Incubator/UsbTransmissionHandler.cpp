#include "Incubator/UsbTransmissionHandler.h"

#include "Data/UsbData.h"
#include "TimeUtils/TimerManager.h"
#include "Utils/CacheManager.h"
#include "bsp_config.h"

namespace Incubator
{
static constexpr uint32_t DEFAULT_PERIODICITY_IN_MS = 1000U;

static const uint8_t ALIVE_CMD[]         = "alive\n";
static constexpr uint16_t ALIVE_CMD_SIZE = sizeof(ALIVE_CMD) - 1U;

static const uint8_t HELP_RESPONSE[]         = "start: starts periodic\nstop: stops periodic\n";
static constexpr uint16_t HELP_RESPONSE_SIZE = sizeof(HELP_RESPONSE) - 1U;

auto UsbTransmissionHandler::Initialize(void) -> void
{
  m_PeriodicTxTimer = TimeUtils::TimerManager::CreateMillisecondTimer();
  Data::UsbData usbData;
  if (Utils::CacheManager::Get(usbData))
  {
    m_PeriodicTxTimer->SetDuration(usbData.m_TransmissionPeriodicity);
  }
  else
  {
    m_PeriodicTxTimer->SetDuration(DEFAULT_PERIODICITY_IN_MS);
  }
  m_PeriodicTxTimer->Start();
}

auto UsbTransmissionHandler::Run(void) -> void
{
  Data::UsbData usbData;
  static_cast<void>(Utils::CacheManager::Get(usbData));
  if (usbData.m_HelpRequested)
  {
    if (bsp_usb_send_data(HELP_RESPONSE, HELP_RESPONSE_SIZE))
    {
      usbData.m_HelpRequested = false;
      Utils::CacheManager::Write(usbData);
    }
  }
  else if (m_PeriodicTxTimer->IsFinished())
  {
    if (usbData.m_TransmissionPeriodicity == 0U)
    {
      m_PeriodicTxTimer->SetDuration(DEFAULT_PERIODICITY_IN_MS);
    }
    else
    {
      m_PeriodicTxTimer->SetDuration(usbData.m_TransmissionPeriodicity);
      static_cast<void>(bsp_usb_send_data(ALIVE_CMD, ALIVE_CMD_SIZE));
    }
    m_PeriodicTxTimer->Start();
  }
  else
  {
    // intentionally left blank
  }
}

} // namespace Incubator
