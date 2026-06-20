#include "Incubator/View/Screen/ScreenFacade.h"

#include "TimeUtils/TimerManager.h"

namespace Incubator
{
void ScreenFacade::ControlMainScreenReturnTimeout()
{
  if (SCREEN_TYPE_MAIN == m_CurrentScreen->GetScreenType())
  {
    m_MainScreenReturnTimerTask->Stop();
  }
  else
  {
    if (false == m_MainScreenReturnTimerTask->IsRunning())
    {
      m_MainScreenReturnTimerTask->Start();
    }
    else if (m_MainScreenReturnTimerTask->IsFinished())
    {
      m_MainScreenReturnTimerTask->Stop();
      m_CurrentScreen->Reset();
      m_CurrentScreen = &m_MainScreen;
      m_MainScreen.OnInitial();
    }
    else
    {
      // intentionally left blank
    }
  }
}

ScreenFacade::ScreenFacade()
    : m_Lcd{nullptr}, m_ScreenList{nullptr}, m_CurrentScreen{nullptr},
      m_MainScreenReturnTimerTask{nullptr}, m_MainScreenReturnTimerStarted{false}
{
}

ScreenFacade::~ScreenFacade()
{
}

void ScreenFacade::Initialize(Lcd2004 *tc2004Lcd, const DataChangedEventHandlers *eventHandlers)
{
  m_Lcd = tc2004Lcd;
  m_DataChangedEventHandlers.Reset();
  m_DataChangedEventHandlers.Copy(*eventHandlers);

  m_MainScreen.Initialize(tc2004Lcd);
  m_MenuScreen.Initialize(tc2004Lcd);
  m_SensorsStatusScreen.Initialize(tc2004Lcd);
  m_SettingsScreen.Initialize(tc2004Lcd);
  m_IncubatorSettingsScreen.Initialize(tc2004Lcd);
  m_TimeSettingsScreen.Initialize(tc2004Lcd,
                                  &m_ChangedIncubatorInformationData.m_TimeInformationData);
  m_TemperatureSettingsScreen.Initialize(tc2004Lcd);
  m_HumiditySettingsScreen.Initialize(tc2004Lcd);
  m_TemperatureDataSetScreen.Initialize(tc2004Lcd, &m_DataChangedEventHandlers,
                                        &m_CurrentIncubatorInformationData,
                                        &m_ChangedIncubatorInformationData);
  m_TemperatureLastDaysDataSetScreen.Initialize(tc2004Lcd, &m_DataChangedEventHandlers,
                                                &m_CurrentIncubatorInformationData,
                                                &m_ChangedIncubatorInformationData);
  m_HumidityDataSetScreen.Initialize(tc2004Lcd, &m_DataChangedEventHandlers,
                                     &m_CurrentIncubatorInformationData,
                                     &m_ChangedIncubatorInformationData);
  m_HumidityLastDaysDataSetScreen.Initialize(tc2004Lcd, &m_DataChangedEventHandlers,
                                             &m_CurrentIncubatorInformationData,
                                             &m_ChangedIncubatorInformationData);
  m_DefaultsSettingsScreen.Initialize(tc2004Lcd, &m_ChangedIncubatorInformationData.m_SettingsData);
  m_SaveQuestionScreen.Initialize(tc2004Lcd, &m_DataChangedEventHandlers,
                                  &m_ChangedIncubatorInformationData.m_SettingsData);
  m_TimeResetQuestionScreen.Initialize(tc2004Lcd, &m_DataChangedEventHandlers,
                                       &m_ChangedIncubatorInformationData.m_TimeInformationData);
  m_CurrentTimeSettingsScreen.Initialize(tc2004Lcd);
  m_CurrentDayDataSetScreen.Initialize(tc2004Lcd, &m_DataChangedEventHandlers,
                                       &m_CurrentIncubatorInformationData,
                                       &m_ChangedIncubatorInformationData);
  m_CurrentHourDataSetScreen.Initialize(tc2004Lcd, &m_DataChangedEventHandlers,
                                        &m_CurrentIncubatorInformationData,
                                        &m_ChangedIncubatorInformationData);
  m_CurrentMinuteDataSetScreen.Initialize(tc2004Lcd, &m_DataChangedEventHandlers,
                                          &m_CurrentIncubatorInformationData,
                                          &m_ChangedIncubatorInformationData);
  m_IncubatorTimeSettingsScreen.Initialize(tc2004Lcd);
  m_TotalDayDataSetScreen.Initialize(tc2004Lcd, &m_DataChangedEventHandlers,
                                     &m_CurrentIncubatorInformationData,
                                     &m_ChangedIncubatorInformationData);
  m_LastDayDataSetScreen.Initialize(tc2004Lcd, &m_DataChangedEventHandlers,
                                    &m_CurrentIncubatorInformationData,
                                    &m_ChangedIncubatorInformationData);
  m_AdministatorSettingsScreen.Initialize(tc2004Lcd);
  m_TemperaturePidSettingsScreen.Initialize(tc2004Lcd);
  m_PDataSetScreen.Initialize(tc2004Lcd, &m_DataChangedEventHandlers,
                              &m_CurrentIncubatorInformationData,
                              &m_ChangedIncubatorInformationData);
  m_IDataSetScreen.Initialize(tc2004Lcd, &m_DataChangedEventHandlers,
                              &m_CurrentIncubatorInformationData,
                              &m_ChangedIncubatorInformationData);
  m_DDataSetScreen.Initialize(tc2004Lcd, &m_DataChangedEventHandlers,
                              &m_CurrentIncubatorInformationData,
                              &m_ChangedIncubatorInformationData);
  m_HysterisisHumiditySettingsScreen.Initialize(tc2004Lcd);
  m_UpperHysterisisHumidityDataSetScreen.Initialize(tc2004Lcd, &m_DataChangedEventHandlers,
                                                    &m_CurrentIncubatorInformationData,
                                                    &m_ChangedIncubatorInformationData);
  m_LowerHysterisisHumidityDataSetScreen.Initialize(tc2004Lcd, &m_DataChangedEventHandlers,
                                                    &m_CurrentIncubatorInformationData,
                                                    &m_ChangedIncubatorInformationData);
  m_AdministratorResetQuestionScreen.Initialize(tc2004Lcd, &m_DataChangedEventHandlers,
                                                &m_ChangedIncubatorInformationData.m_AdminData);

  m_ScreenList[SCREEN_TYPE_MAIN]                           = &m_MainScreen;
  m_ScreenList[SCREEN_TYPE_MENU]                           = &m_MenuScreen;
  m_ScreenList[SCREEN_TYPE_SENSORS_STATUS]                 = &m_SensorsStatusScreen;
  m_ScreenList[SCREEN_TYPE_SETTINGS]                       = &m_SettingsScreen;
  m_ScreenList[SCREEN_TYPE_INCUBATOR_SETTINGS]             = &m_IncubatorSettingsScreen;
  m_ScreenList[SCREEN_TYPE_TIME_SETTINGS]                  = &m_TimeSettingsScreen;
  m_ScreenList[SCREEN_TYPE_TEMPERATURE_SETTINGS]           = &m_TemperatureSettingsScreen;
  m_ScreenList[SCREEN_TYPE_HUMIDITY_SETTINGS]              = &m_HumiditySettingsScreen;
  m_ScreenList[SCREEN_TYPE_DATA_SET_TEMPERATURE]           = &m_TemperatureDataSetScreen;
  m_ScreenList[SCREEN_TYPE_DATA_SET_TEMPERATURE_LAST_DAYS] = &m_TemperatureLastDaysDataSetScreen;
  m_ScreenList[SCREEN_TYPE_DATA_SET_HUMIDITY]              = &m_HumidityDataSetScreen;
  m_ScreenList[SCREEN_TYPE_DATA_SET_HUMIDITY_LAST_DAYS]    = &m_HumidityLastDaysDataSetScreen;
  m_ScreenList[SCREEN_TYPE_DEFAULTS_SETTINGS]              = &m_DefaultsSettingsScreen;
  m_ScreenList[SCREEN_TYPE_QUESTION_SAVE]                  = &m_SaveQuestionScreen;
  m_ScreenList[SCREEN_TYPE_QUESTION_TIME_RESET]            = &m_TimeResetQuestionScreen;
  m_ScreenList[SCREEN_TYPE_CURRENT_TIME_SETTINGS]          = &m_CurrentTimeSettingsScreen;
  m_ScreenList[SCREEN_TYPE_DATA_SET_CURRENT_DAY]           = &m_CurrentDayDataSetScreen;
  m_ScreenList[SCREEN_TYPE_DATA_SET_CURRENT_HOUR]          = &m_CurrentHourDataSetScreen;
  m_ScreenList[SCREEN_TYPE_DATA_SET_CURRENT_MINUTE]        = &m_CurrentMinuteDataSetScreen;
  m_ScreenList[SCREEN_TYPE_INCUBATOR_TIME_SETTINGS]        = &m_IncubatorTimeSettingsScreen;
  m_ScreenList[SCREEN_TYPE_DATA_SET_TOTAL_DAY_COUNT]       = &m_TotalDayDataSetScreen;
  m_ScreenList[SCREEN_TYPE_DATA_SET_LAST_DAY_COUNT]        = &m_LastDayDataSetScreen;
  m_ScreenList[SCREEN_TYPE_ADMINISTRATOR_SETTINGS]         = &m_AdministatorSettingsScreen;
  m_ScreenList[SCREEN_TYPE_TEMPERATURE_PID]                = &m_TemperaturePidSettingsScreen;
  m_ScreenList[SCREEN_TYPE_DATA_SET_P]                     = &m_PDataSetScreen;
  m_ScreenList[SCREEN_TYPE_DATA_SET_I]                     = &m_IDataSetScreen;
  m_ScreenList[SCREEN_TYPE_DATA_SET_D]                     = &m_DDataSetScreen;
  m_ScreenList[SCREEN_TYPE_HYSTERISIS_HUMIDITY]            = &m_HysterisisHumiditySettingsScreen;
  m_ScreenList[SCREEN_TYPE_DATA_SET_UPPER_HYSTERISIS] = &m_UpperHysterisisHumidityDataSetScreen;
  m_ScreenList[SCREEN_TYPE_DATA_SET_LOWER_HYSTERISIS] = &m_LowerHysterisisHumidityDataSetScreen;
  m_ScreenList[SCREEN_TYPE_QUESTION_ADMIN_RESET]      = &m_AdministratorResetQuestionScreen;

  m_CurrentScreen = &m_MainScreen;

  constexpr uint32_t MAIN_SCREEN_RETURN_DURATION_IN_MILLISECOND = static_cast<uint32_t>(180000UL);

  m_MainScreenReturnTimerTask = TimeUtils::TimerManager::CreateMillisecondTimer();
  m_MainScreenReturnTimerTask->SetDuration(MAIN_SCREEN_RETURN_DURATION_IN_MILLISECOND);
  m_MainScreenReturnTimerTask->Start();
}

void ScreenFacade::UpdateAdminData(const AdminData &data)
{
  m_CurrentIncubatorInformationData.m_AdminData.Copy(data);
}

void ScreenFacade::UpdateSettingsData(const SettingsData &data)
{
  m_CurrentIncubatorInformationData.m_SettingsData.Copy(data);
  m_MainScreen.UpdateSettingsData(data);
}

void ScreenFacade::UpdateTimeInformationData(const TimeInformationData &data)
{
  m_CurrentIncubatorInformationData.m_TimeInformationData.Copy(data);
  m_MainScreen.UpdateTimeInformationData(data);
}

void ScreenFacade::UpdateTemperature(const int32_t &temperatureInMilliCelcius)
{
  m_MainScreen.UpdateTemperature(temperatureInMilliCelcius);
}

void ScreenFacade::OnTemperatureFailure()
{
  m_CurrentScreen = &m_MainScreen;
  m_MainScreen.OnTemperatureFailure();
}

void ScreenFacade::UpdateHumidity(const uint8_t &humidityInPrecentage)
{
  m_MainScreen.UpdateHumidity(humidityInPrecentage);
}

void ScreenFacade::OnHumidityFailure()
{
  m_MainScreen.OnHumidityFailure();
}

void ScreenFacade::OnModelFailure()
{
  m_CurrentScreen = &m_MainScreen;
  m_MainScreen.OnModelFailure();
}

void ScreenFacade::UpdateSensorsStatus(const SensorsStatusData &data)
{
  m_SensorsStatusScreen.UpdateSensorsStatus(data);
}

void ScreenFacade::OnUserAction(const JoystickEvent &event)
{
  if (m_MainScreenReturnTimerTask->IsRunning())
  {
    m_MainScreenReturnTimerTask->Start();
  }
  const EnumScreenType screenType = m_CurrentScreen->GetScreenType();
  m_CurrentScreen->OnUserAction(event);
  const EnumScreenType nextScreenType = m_CurrentScreen->GetNextScreen();
  if (screenType != nextScreenType)
  {
    const EnumScreenType nextValidScreenType =
      (static_cast<uint32_t>(nextScreenType) < static_cast<uint32_t>(SCREEN_TYPE_SIZE))
        ? nextScreenType
        : SCREEN_TYPE_MAIN;
    m_CurrentScreen = m_ScreenList[nextValidScreenType];
    m_CurrentScreen->SetPreviousScreen(screenType);
    m_CurrentScreen->OnInitial();
  }
}

void ScreenFacade::Run()
{
  ControlMainScreenReturnTimeout();
  m_CurrentScreen->Run();
}

} // namespace Incubator
