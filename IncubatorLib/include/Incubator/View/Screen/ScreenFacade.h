#ifndef INCUBATOR_SCREENFACADE_H
#define INCUBATOR_SCREENFACADE_H
#include "AdministatorSettingsScreen.h"
#include "CurrentTimeSettingsScreen.h"
#include "DataSetScreen/CurrentDayDataSetScreen.h"
#include "DataSetScreen/CurrentHourDataSetScreen.h"
#include "DataSetScreen/CurrentMinuteDataSetScreen.h"
#include "DataSetScreen/DDataSetScreen.h"
#include "DataSetScreen/HumidityDataSetScreen.h"
#include "DataSetScreen/HumidityLastDaysDataSetScreen.h"
#include "DataSetScreen/IDataSetScreen.h"
#include "DataSetScreen/LastDayDataSetScreen.h"
#include "DataSetScreen/LowerHysterisisHumidityDataSetScreen.h"
#include "DataSetScreen/PDataSetScreen.h"
#include "DataSetScreen/TemperatureDataSetScreen.h"
#include "DataSetScreen/TemperatureLastDaysDataSetScreen.h"
#include "DataSetScreen/TotalDayDataSetScreen.h"
#include "DataSetScreen/UpperHysterisisHumidityDataSetScreen.h"
#include "DefaultsSettingsScreen.h"
#include "HumiditySettingsScreen.h"
#include "HysterisisHumiditySettingsScreen.h"
#include "Incubator/IncubatorData/IncubatorInformationData.h"
#include "Incubator/Lcd2004.h"
#include "Incubator/View/DataChangedEventHandler/DataChangedEventHandlers.h"
#include "IncubatorSettingsScreen.h"
#include "IncubatorTimeSettingsScreen.h"
#include "MainScreen.h"
#include "MenuScreen.h"
#include "QuestionScreen/AdministratorResetQuestionScreen.h"
#include "QuestionScreen/SaveQuestionScreen.h"
#include "QuestionScreen/TimeResetQuestionScreen.h"
#include "SensorsStatusScreen.h"
#include "SettingsScreen.h"
#include "TemperaturePidSettingsScreen.h"
#include "TemperatureSettingsScreen.h"
#include "TimeSettingsScreen.h"
#include "TimeUtils/MillisecondTimer.h"

namespace Incubator
{
class ScreenFacade
{
public:
  ScreenFacade();
  ~ScreenFacade();
  void Initialize(Lcd2004 *tc2004Lcd, const DataChangedEventHandlers *eventHandlers);

  void UpdateAdminData(const AdminData &data);
  void UpdateSettingsData(const SettingsData &data);
  void UpdateTimeInformationData(const TimeInformationData &data);
  void UpdateTemperature(const int32_t &temperatureInMilliCelcius);
  void OnTemperatureFailure();
  void UpdateHumidity(const uint8_t &humidityInPrecentage);
  void OnHumidityFailure();
  void UpdateTime(const uint32_t timestampInSeconds);

  void OnModelFailure();
  void UpdateSensorsStatus(const SensorsStatusData &data);
  void OnUserAction(const JoystickEvent &event);
  void Run();

private:
  Lcd2004 *m_Lcd;
  AScreen *m_ScreenList[SCREEN_TYPE_SIZE];
  AScreen *m_CurrentScreen;
  MainScreen m_MainScreen;
  MenuScreen m_MenuScreen;
  SensorsStatusScreen m_SensorsStatusScreen;
  SettingsScreen m_SettingsScreen;
  TimeSettingsScreen m_TimeSettingsScreen;
  IncubatorSettingsScreen m_IncubatorSettingsScreen;
  TemperatureSettingsScreen m_TemperatureSettingsScreen;
  HumiditySettingsScreen m_HumiditySettingsScreen;
  TemperatureDataSetScreen m_TemperatureDataSetScreen;
  TemperatureLastDaysDataSetScreen m_TemperatureLastDaysDataSetScreen;
  HumidityDataSetScreen m_HumidityDataSetScreen;
  HumidityLastDaysDataSetScreen m_HumidityLastDaysDataSetScreen;
  DefaultsSettingsScreen m_DefaultsSettingsScreen;
  SaveQuestionScreen m_SaveQuestionScreen;
  TimeResetQuestionScreen m_TimeResetQuestionScreen;
  CurrentTimeSettingsScreen m_CurrentTimeSettingsScreen;
  CurrentDayDataSetScreen m_CurrentDayDataSetScreen;
  CurrentHourDataSetScreen m_CurrentHourDataSetScreen;
  CurrentMinuteDataSetScreen m_CurrentMinuteDataSetScreen;
  IncubatorTimeSettingsScreen m_IncubatorTimeSettingsScreen;
  TotalDayDataSetScreen m_TotalDayDataSetScreen;
  LastDayDataSetScreen m_LastDayDataSetScreen;
  AdministatorSettingsScreen m_AdministatorSettingsScreen;
  TemperaturePidSettingsScreen m_TemperaturePidSettingsScreen;
  PDataSetScreen m_PDataSetScreen;
  IDataSetScreen m_IDataSetScreen;
  DDataSetScreen m_DDataSetScreen;
  HysterisisHumiditySettingsScreen m_HysterisisHumiditySettingsScreen;
  UpperHysterisisHumidityDataSetScreen m_UpperHysterisisHumidityDataSetScreen;
  LowerHysterisisHumidityDataSetScreen m_LowerHysterisisHumidityDataSetScreen;
  AdministratorResetQuestionScreen m_AdministratorResetQuestionScreen;

  DataChangedEventHandlers m_DataChangedEventHandlers;

  IncubatorInformationData m_CurrentIncubatorInformationData;
  IncubatorInformationData m_ChangedIncubatorInformationData;
  TimeUtils::MillisecondTimer *m_MainScreenReturnTimerTask;
  bool m_MainScreenReturnTimerStarted;

private:
  void ControlMainScreenReturnTimeout();
};
} // namespace Incubator

#endif // INCUBATOR_SCREENFACADE_H
