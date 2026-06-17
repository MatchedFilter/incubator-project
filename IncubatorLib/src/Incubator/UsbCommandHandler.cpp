#include "Incubator/UsbCommandHandler.h"

#include "Data/UsbData.h"
#include "Utils/CacheManager.h"
#include "bsp_config.h"

#include <cstring>

namespace Incubator
{

enum class UsbCommandType
{
  Invalid = 0,
  Reset,
  StopPeriodic,
  StartPeriodic,
  Help
};

static const uint8_t RESET_CMD[]                  = "reset\n";
static constexpr uint16_t RESET_CMD_SIZE          = sizeof(RESET_CMD) - 1U;
static const uint8_t STOP_PERIODIC_CMD[]          = "stop\n";
static constexpr uint16_t STOP_PERIODIC_CMD_SIZE  = sizeof(STOP_PERIODIC_CMD) - 1U;
static const uint8_t START_PERIODIC_CMD[]         = "start\n";
static constexpr uint16_t START_PERIODIC_CMD_SIZE = sizeof(START_PERIODIC_CMD) - 1U;
static const uint8_t HELP_CMD[]                   = "help\n";
static constexpr uint16_t HELP_CMD_SIZE           = sizeof(HELP_CMD) - 1U;

static auto GetUsbCommandType(void) -> UsbCommandType;
static auto HandleReset(void) -> void;
static auto HandleStopPeriodic(void) -> void;
static auto HandleStartPeriodic(void) -> void;
static auto HandleHelp(void) -> void;

auto UsbCommandHandler::Run(void) -> void
{
  if (bsp_is_usb_data_ready())
  {
    const auto usbCommand = GetUsbCommandType();
    switch (usbCommand)
    {
      case UsbCommandType::Reset:
      {
        HandleReset();
        break;
      }

      case UsbCommandType::StopPeriodic:
      {
        HandleStopPeriodic();
        break;
      }

      case UsbCommandType::StartPeriodic:
      {
        HandleStartPeriodic();
        break;
      }

      case UsbCommandType::Help:
      {
        HandleHelp();
        break;
      }

      case UsbCommandType::Invalid:
      default:
      {
        break;
      }
    }
  }
  bsp_clear_usb_data_ready();
}

static auto GetUsbCommandType(void) -> UsbCommandType
{
  UsbCommandType command = UsbCommandType::Invalid;
  uint32_t usbDataLength = 0U;
  const uint8_t *usbData = bsp_get_usb_data(&usbDataLength);
  if (usbData != NULL)
  {
    if (usbDataLength == RESET_CMD_SIZE)
    {
      if (std::memcmp(usbData, RESET_CMD, RESET_CMD_SIZE) == 0)
      {
        command = UsbCommandType::Reset;
      }
    }
    if (usbDataLength == STOP_PERIODIC_CMD_SIZE)
    {
      if (std::memcmp(usbData, STOP_PERIODIC_CMD, STOP_PERIODIC_CMD_SIZE) == 0)
      {
        command = UsbCommandType::StopPeriodic;
      }
    }
    if (usbDataLength == START_PERIODIC_CMD_SIZE)
    {
      if (std::memcmp(usbData, START_PERIODIC_CMD, START_PERIODIC_CMD_SIZE) == 0)
      {
        command = UsbCommandType::StartPeriodic;
      }
    }
    if (usbDataLength == HELP_CMD_SIZE)
    {
      if (std::memcmp(usbData, HELP_CMD, HELP_CMD_SIZE) == 0)
      {
        command = UsbCommandType::Help;
      }
    }
    else
    {
      // intentionally left blank
    }
  }
  return command;
}

static auto HandleReset(void) -> void
{
  bsp_reset();
}

static auto HandleStartPeriodic(void) -> void
{
  Data::UsbData usbData;
  static_cast<void>(Utils::CacheManager::Get(usbData));
  usbData.m_TransmissionPeriodicity = 1000U;
  Utils::CacheManager::Write(usbData);
}

static auto HandleStopPeriodic(void) -> void
{
  Data::UsbData usbData;
  static_cast<void>(Utils::CacheManager::Get(usbData));
  usbData.m_TransmissionPeriodicity = 0U;
  Utils::CacheManager::Write(usbData);
}

static auto HandleHelp(void) -> void
{
  Data::UsbData usbData;
  static_cast<void>(Utils::CacheManager::Get(usbData));
  usbData.m_HelpRequested = true;
  Utils::CacheManager::Write(usbData);
}

} // namespace Incubator
