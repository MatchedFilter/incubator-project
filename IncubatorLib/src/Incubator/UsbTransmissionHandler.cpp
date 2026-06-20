#include "Incubator/UsbTransmissionHandler.h"

#include "Data/UsbData.h"
#include "TimeUtils/TimerManager.h"
#include "Utils/CacheManager.h"
#include "Utils/StringUtils.h"
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
      char txStr[64]   = {0};
      uint8_t index    = 0U;
      txStr[index++]   = 'b';
      txStr[index++]   = 'm';
      txStr[index++]   = 'e';
      txStr[index++]   = '2';
      txStr[index++]   = '8';
      txStr[index++]   = '0';
      txStr[index++]   = ':';
      txStr[index++]   = ' ';
      uint8_t humidity = 0U;
      int32_t temp;
      if (bsp_bme280_read_humidity(&humidity) && bsp_bme280_read_temperature(&temp))
      {
        txStr[index++]  = 'O';
        txStr[index++]  = 'K';
        txStr[index++]  = ' ';
        txStr[index++]  = 't';
        txStr[index++]  = 'm';
        txStr[index++]  = 'p';
        txStr[index++]  = ':';
        txStr[index++]  = ' ';
        index          += Utils::StringUtils::ToCharArray(temp, txStr, index);
        txStr[index++]  = ',';
        txStr[index++]  = ' ';
        txStr[index++]  = 'h';
        txStr[index++]  = 'm';
        txStr[index++]  = 'd';
        txStr[index++]  = ':';
        txStr[index++]  = ' ';
        index          += Utils::StringUtils::ToCharArray(humidity, txStr, index);
      }
      else
      {
        txStr[index++] = 'F';
        txStr[index++] = 'A';
        txStr[index++] = 'I';
        txStr[index++] = 'L';
      }
      txStr[index++] = '\n';
      m_PeriodicTxTimer->SetDuration(usbData.m_TransmissionPeriodicity);
      static_cast<void>(bsp_usb_send_data((uint8_t *) txStr, index));
    }
    m_PeriodicTxTimer->Start();
  }
  else
  {
    // intentionally left blank
  }
}

} // namespace Incubator
