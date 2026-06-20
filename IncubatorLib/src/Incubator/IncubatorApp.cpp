#include "Incubator/IncubatorApp.h"

#include "Data/UsbData.h"
#include "TimeUtils/TimerManager.h"
#include "Utils/CacheManager.h"
#include "bsp_config.h"

#include <cstring>

namespace Incubator
{

auto IncubatorApp::Initialize(void) -> void
{
  Data::UsbData usbData;
  usbData.m_TransmissionPeriodicity = 1000U;
  Utils::CacheManager::Write(usbData);

  m_Timer = TimeUtils::TimerManager::CreateMillisecondTimer();
  m_Timer->SetDuration(250U);
  m_Timer->Start();

  m_UsbTransmissionHandler.Initialize();

  m_Presenter.Initialize(&m_Lcd2004View, &m_InternalFlashModel);
}

auto IncubatorApp::Run(void) -> void
{
  if (m_Timer->IsFinished())
  {
    bsp_internal_led_toggle();
    m_Timer->Start();
  }
  m_UsbCommandHandler.Run();
  m_UsbTransmissionHandler.Run();

  m_Presenter.Run();
  m_Lcd2004View.Run();
}
} // namespace Incubator
