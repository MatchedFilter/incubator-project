#include "Incubator/View/Lcd2004View.h"

#include "Incubator/View/JoystickEvent.h"
#include "TimeUtils/TimerManager.h"
#include "bsp_config.h"

namespace Incubator
{
void Lcd2004View::ReadJoystick()
{
  if (m_JoystickSensorTimerTask->IsFinished())
  {
    m_JoystickSensorTimerTask->Start();
    constexpr uint32_t UPPER_THRESHOLD = static_cast<uint32_t>(2900UL);
    constexpr uint32_t LOWER_THRESHOLD = static_cast<uint32_t>(1100UL);
    uint16_t xValue                    = 0U;
    uint16_t yValue                    = 0U;
    bsp_joystick_read_positions(&xValue, &yValue);

    if (yValue > UPPER_THRESHOLD)
    {
      m_bDownShifted = true;
    }
    else if (yValue < LOWER_THRESHOLD)
    {
      m_bUpShifted = true;
    }
    else
    {
      if (m_bUpShifted)
      {
        const JoystickEvent event = {.bIsUpPressed     = true,
                                     .bIsDownPressed   = false,
                                     .bIsRightPressed  = false,
                                     .bIsLeftPressed   = false,
                                     .bIsButtonPressed = false};
        OnUserAction(event);
      }
      else if (m_bDownShifted)
      {
        const JoystickEvent event = {.bIsUpPressed     = false,
                                     .bIsDownPressed   = true,
                                     .bIsRightPressed  = false,
                                     .bIsLeftPressed   = false,
                                     .bIsButtonPressed = false};
        OnUserAction(event);
      }
      else
      {
      }
      m_bUpShifted   = false;
      m_bDownShifted = false;
    }

    if (xValue > UPPER_THRESHOLD)
    {
      m_bRightShifted = true;
      if (m_bLeftShifted)
      {
        const JoystickEvent event = {.bIsUpPressed     = false,
                                     .bIsDownPressed   = false,
                                     .bIsRightPressed  = false,
                                     .bIsLeftPressed   = true,
                                     .bIsButtonPressed = false};
        OnUserAction(event);
      }
    }
    else if (xValue < LOWER_THRESHOLD)
    {
      m_bLeftShifted = true;
      if (m_bRightShifted)
      {
        const JoystickEvent event = {.bIsUpPressed     = false,
                                     .bIsDownPressed   = false,
                                     .bIsRightPressed  = true,
                                     .bIsLeftPressed   = false,
                                     .bIsButtonPressed = false};
        OnUserAction(event);
      }
    }
    else
    {
      if (m_bRightShifted)
      {
        const JoystickEvent event = {.bIsUpPressed     = false,
                                     .bIsDownPressed   = false,
                                     .bIsRightPressed  = true,
                                     .bIsLeftPressed   = false,
                                     .bIsButtonPressed = false};
        OnUserAction(event);
      }
      else if (m_bLeftShifted)
      {
        const JoystickEvent event = {.bIsUpPressed     = false,
                                     .bIsDownPressed   = false,
                                     .bIsRightPressed  = false,
                                     .bIsLeftPressed   = true,
                                     .bIsButtonPressed = false};
        OnUserAction(event);
      }
      else
      {
      }
      m_bRightShifted = false;
      m_bLeftShifted  = false;
    }

    const bool bIsSwitchPressed = bsp_joystick_is_switch_pressed();
    if (false == bIsSwitchPressed)
    {
      if (m_bSwitchPressed)
      {
        const JoystickEvent event = {.bIsUpPressed     = false,
                                     .bIsDownPressed   = false,
                                     .bIsRightPressed  = false,
                                     .bIsLeftPressed   = false,
                                     .bIsButtonPressed = true};
        OnUserAction(event);
      }
    }
    m_bSwitchPressed = bIsSwitchPressed;
  }
}

void Lcd2004View::OnUserAction(const JoystickEvent event)
{
  m_ScreenFacade.OnUserAction(event);
}

Lcd2004View::Lcd2004View()
    : m_bUpShifted{false}, m_bDownShifted{false}, m_bRightShifted{false}, m_bLeftShifted{false},
      m_bSwitchPressed{false}, m_JoystickSensorTimerTask{nullptr}
{
}

Lcd2004View::~Lcd2004View()
{
}

bool Lcd2004View::Initialize(const DataChangedEventHandlers *eventHandlers)
{
  bool bResult              = true;
  m_JoystickSensorTimerTask = TimeUtils::TimerManager::CreateMillisecondTimer();
  m_JoystickSensorTimerTask->SetDuration(100U);
  m_JoystickSensorTimerTask->Start();
  m_TC2004Lcd.MoveCursor(0U, 0U);
  m_ScreenFacade.Initialize(&m_TC2004Lcd, eventHandlers);

  return bResult;
}

void Lcd2004View::UpdateTemperature(const double temperatureInCelcius)
{
  m_ScreenFacade.UpdateTemperature(temperatureInCelcius);
}

void Lcd2004View::OnTemperatureFailure()
{
  m_ScreenFacade.OnTemperatureFailure();
}

void Lcd2004View::UpdateHumidity(const uint8_t humidityInPercentage)
{
  m_ScreenFacade.UpdateHumidity(humidityInPercentage);
}

void Lcd2004View::OnHumidityFailure()
{
  m_ScreenFacade.OnHumidityFailure();
}

void Lcd2004View::UpdateAdminData(const AdminData &data)
{
  m_ScreenFacade.UpdateAdminData(data);
}

void Lcd2004View::UpdateSettingsData(const SettingsData &data)
{
  m_ScreenFacade.UpdateSettingsData(data);
}

void Lcd2004View::UpdateTimeInformationData(const TimeInformationData &data)
{
  m_ScreenFacade.UpdateTimeInformationData(data);
}

void Lcd2004View::OnModelFailure()
{
  m_ScreenFacade.OnModelFailure();
}

void Lcd2004View::UpdateSensorsStatus(const SensorsStatusData &data)
{
  m_ScreenFacade.UpdateSensorsStatus(data);
}

void Lcd2004View::Run()
{
  ReadJoystick();
  m_ScreenFacade.Run();
  m_TC2004Lcd.Run();
}

} // namespace Incubator
