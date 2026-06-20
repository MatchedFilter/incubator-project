#include "Incubator/Presenter/Presenter.h"

#include "TimeUtils/TimeSettings.h"
#include "TimeUtils/TimerManager.h"
#include "bsp_config.h"

#include <cstddef>

namespace Incubator
{

bool Presenter::ReadModel(IModel *model, AdminData &pid, SettingsData &settings,
                          TimeInformationData &timeInformation)
{
  bool bResult = false;
  if (model != nullptr)
  {
    constexpr uint32_t MAX_TRY_COUNT = static_cast<uint32_t>(5UL);
    bool bTimeRead                   = false;
    bool bSettingsRead               = false;
    bool bPidRead                    = false;
    for (uint32_t i = static_cast<uint32_t>(0UL); i < MAX_TRY_COUNT; i++)
    {
      if (false == bTimeRead)
      {
        bTimeRead = model->Get(timeInformation);
      }
      if (false == bSettingsRead)
      {
        bSettingsRead = model->Get(settings);
      }
      if (false == bPidRead)
      {
        bPidRead = model->Get(pid);
      }
      if (bTimeRead && bSettingsRead && bPidRead)
      {
        bResult = true;
        break;
      }
    }
  }
  return bResult;
}

bool Presenter::UpdateModel(IModel *model, AdminData &data)
{
  bool bResult                     = false;
  constexpr uint32_t MAX_TRY_COUNT = static_cast<uint32_t>(5UL);
  if (model != nullptr)
  {
    for (uint32_t i = static_cast<uint32_t>(0UL); i < MAX_TRY_COUNT; i++)
    {
      if (model->Update(data))
      {
        bResult = true;
        break;
      }
    }
  }
  return bResult;
}

bool Presenter::UpdateModel(IModel *model, SettingsData &data)
{
  bool bResult                     = false;
  constexpr uint32_t MAX_TRY_COUNT = static_cast<uint32_t>(5UL);
  if (model != nullptr)
  {

    for (uint32_t i = static_cast<uint32_t>(0UL); i < MAX_TRY_COUNT; i++)
    {
      if (model->Update(data))
      {
        bResult = true;
        break;
      }
    }
  }
  return bResult;
}

bool Presenter::UpdateModel(IModel *model, TimeInformationData &data)
{
  bool bResult                     = false;
  constexpr uint32_t MAX_TRY_COUNT = static_cast<uint32_t>(5UL);
  if (model != nullptr)
  {
    for (uint32_t i = static_cast<uint32_t>(0UL); i < MAX_TRY_COUNT; i++)
    {
      if (model->Update(data))
      {
        bResult = true;
        break;
      }
    }
  }
  return bResult;
}

bool Presenter::SyncModels(AdminData &pid, SettingsData &settings,
                           TimeInformationData &timeInformation)
{
  AdminData pid1;
  SettingsData settings1;
  TimeInformationData timeInformation1;
  timeInformation1.Reset();
  const bool bModelValid = ReadModel(m_Model, pid1, settings1, timeInformation1);

  bool bResult = true;
  if (bModelValid)
  {
    pid.Copy(pid1);
    settings.Copy(settings1);
    timeInformation.Copy(timeInformation1);

    OnUpdate(pid);
    OnUpdate(settings);
    OnUpdate(timeInformation);
  }
  return bResult;
}

Presenter::Presenter()
    : m_View{nullptr}, m_Model{nullptr}, m_bIsInitialized{false}, m_ModelUpdateTimerTask{nullptr},
      m_SensorReadingTimer{nullptr}, m_TemperatureControllerTimer{nullptr},
      m_HumidityControllerTimer{nullptr}, m_HumidityInPercentage{0U},
      m_TemperatureInMilliCelcius{0}, m_PreviousPidTimestamp{0}, m_HeaterOnPeriod{0},
      m_HeaterControlTimestamp{0}
{
}

Presenter::~Presenter()
{
}

void Presenter::Initialize(IView *view, IModel *model)
{
  m_View  = view;
  m_Model = model;

  m_ModelUpdateTimerTask = TimeUtils::TimerManager::CreateMillisecondTimer();

  m_SensorReadingTimer = TimeUtils::TimerManager::CreateMillisecondTimer();
  m_SensorReadingTimer->SetDuration(250U);
  m_SensorReadingTimer->Start();

  m_TemperatureControllerTimer = TimeUtils::TimerManager::CreateMillisecondTimer();
  m_TemperatureControllerTimer->SetDuration(20U);
  m_TemperatureControllerTimer->Start();

  m_HumidityControllerTimer = TimeUtils::TimerManager::CreateMillisecondTimer();
  m_HumidityControllerTimer->SetDuration(3000U);
  m_HumidityControllerTimer->Start();

  DataChangedEventHandlers eventHandlers;
  eventHandlers.Reset();
  eventHandlers.m_AdminDataChangedEventHandler           = this;
  eventHandlers.m_SettingsDataChangedEventHandler        = this;
  eventHandlers.m_TimeInformationDataChangedEventHandler = this;

  if (m_View->Initialize(&eventHandlers))
  {
    AdminData adminSettings;
    SettingsData settings;
    TimeInformationData timeInformation;
    adminSettings.Reset();
    settings.Reset();
    timeInformation.Reset();
    // (void) UpdateModel(m_Model, pid);
    // (void) UpdateModel(m_Model, settings);
    // (void) UpdateModel(m_Model, timeInformation);

    if (SyncModels(adminSettings, settings, timeInformation))
    {
      m_bIsInitialized = true;
      m_View->UpdateSettingsData(settings);
      m_View->UpdateTimeInformationData(timeInformation);
      const uint64_t currentTimestampInMillisecond =
        static_cast<uint64_t>(timeInformation.m_CurrentTimestampInSecond);
      TimeUtils::TimeSettings::SetIncubatorTimeInSeconds(currentTimestampInMillisecond);

      constexpr uint32_t MODEL_UPDATE_DURATION_IN_MILLISECOND =
        static_cast<uint32_t>(120UL) * static_cast<uint32_t>(1000UL); // 2 minutes
      m_ModelUpdateTimerTask->SetDuration(MODEL_UPDATE_DURATION_IN_MILLISECOND);
      m_ModelUpdateTimerTask->Start();
    }
    else
    {
      m_View->OnModelFailure();
    }
  }
  m_PreviousPidTimestamp   = bsp_get_time_in_ms();
  m_HeaterControlTimestamp = m_PreviousPidTimestamp;
}

void Presenter::OnUpdate(const AdminData &data)
{
  m_AdminData.Copy(data);
  if (m_Model != nullptr)
  {
    m_Model->Update(data);
  }
  if (m_View != nullptr)
  {
    m_View->UpdateAdminData(data);
  }
  m_HumidityController.SetHumidityThresholds(data.m_UpperHumidityDifference,
                                             data.m_LowerHumidityDifference);

  m_TemperatureController.SetPid(data.m_P, data.m_I, data.m_D);
}

void Presenter::OnUpdate(const SettingsData &data)
{
  m_SettingsData.Copy(data);
  if (m_Model != nullptr)
  {
    m_Model->Update(m_SettingsData);
  }
  if (m_View != nullptr)
  {
    m_View->UpdateSettingsData(m_SettingsData);
  }
  int32_t desiredTemperatureInMilliCelcius = 0;
  uint8_t desiredHumidityInPercentage      = 0U;

  const uint8_t dayCount = static_cast<uint8_t>(
    TimeUtils::TimeSettings::GetIncubatorTimeInSeconds() /
    (static_cast<uint32_t>(60UL) * static_cast<uint32_t>(60UL) * static_cast<uint32_t>(24UL)));
  if (dayCount >= (m_SettingsData.m_TotalIncubationDayCount - m_SettingsData.m_LastDaysCount))
  {
    desiredTemperatureInMilliCelcius = m_SettingsData.m_LastDaysTemperatureInMilliCelcius;
    desiredHumidityInPercentage      = m_SettingsData.m_LastDaysHumidityInPercentage;
  }
  else
  {
    desiredTemperatureInMilliCelcius = m_SettingsData.m_TemperatureInMilliCelcius;
    desiredHumidityInPercentage      = m_SettingsData.m_HumidityInPercentage;
  }

  m_TemperatureController.SetDesiredTemperature(desiredTemperatureInMilliCelcius);
  m_HumidityController.SetDesiredHumidity(desiredHumidityInPercentage);
}

void Presenter::OnUpdate(const TimeInformationData &data)
{
  TimeUtils::TimeSettings::SetIncubatorTimeInSeconds(data.m_CurrentTimestampInSecond);
  if (m_Model != nullptr)
  {
    m_Model->Update(data);
  }
  if (m_View != nullptr)
  {
    m_View->UpdateTimeInformationData(data);
  }
  int32_t desiredTemperatureInMilliCelcius = 0;
  uint8_t desiredHumidityInPercentage      = 0U;

  const uint8_t dayCount = static_cast<uint8_t>(
    TimeUtils::TimeSettings::GetIncubatorTimeInSeconds() /
    (static_cast<uint32_t>(60UL) * static_cast<uint32_t>(60UL) * static_cast<uint32_t>(24UL)));
  if (dayCount >= (m_SettingsData.m_TotalIncubationDayCount - m_SettingsData.m_LastDaysCount))
  {
    desiredTemperatureInMilliCelcius = m_SettingsData.m_LastDaysTemperatureInMilliCelcius;
    desiredHumidityInPercentage      = m_SettingsData.m_LastDaysHumidityInPercentage;
  }
  else
  {
    desiredTemperatureInMilliCelcius = m_SettingsData.m_TemperatureInMilliCelcius;
    desiredHumidityInPercentage      = m_SettingsData.m_HumidityInPercentage;
  }

  m_TemperatureController.SetDesiredTemperature(desiredTemperatureInMilliCelcius);
  m_HumidityController.SetDesiredHumidity(desiredHumidityInPercentage);
}

auto Presenter::ReadSensorsAndUpdateDisplay(void)
{
  bool bme_sensor_is_ok = true;
  if (m_SensorReadingTimer->IsFinished())
  {
    m_SensorReadingTimer->Start();
    bsp_bme280_process_run();
  }

  if (bsp_bme280_read_humidity(&m_HumidityInPercentage))
  {
    m_View->UpdateHumidity(m_HumidityInPercentage);
    m_HumidityController.UpdateHumidityFailStatus(false);
  }
  else
  {
    bme_sensor_is_ok = false;
    m_HumidityController.UpdateHumidityFailStatus(true);
    m_View->OnHumidityFailure();
  }

  if (bsp_bme280_read_temperature(&m_TemperatureInMilliCelcius))
  {
    m_View->UpdateTemperature(m_TemperatureInMilliCelcius);
  }
  else
  {
    bme_sensor_is_ok = false;
    m_View->OnTemperatureFailure();
  }
  if (bme_sensor_is_ok)
  {
    m_SensorsStatusData.m_Bme280Status = SENSOR_STATUS_NO_ERROR;
  }
  else
  {
    m_SensorsStatusData.m_Bme280Status = SENSOR_STATUS_ERROR;
  }
  m_View->UpdateSensorsStatus(m_SensorsStatusData);
}

auto Presenter::ControlTemperature(void)
{
  if (m_TemperatureControllerTimer->IsFinished())
  {
    const uint64_t currentTimestamp = bsp_get_time_in_ms();
    const auto diffTimestamp        = currentTimestamp - m_PreviousPidTimestamp;
    m_PreviousPidTimestamp          = currentTimestamp;

    m_TemperatureControllerTimer->Start();
    m_HeaterOnPeriod = m_TemperatureController.Control(m_TemperatureInMilliCelcius, diffTimestamp);
  }
}
auto Presenter::ControlHumidity(void)
{
  if (m_HumidityControllerTimer->IsFinished())
  {
    m_HumidityControllerTimer->Start();
    const auto humidityGeneratorState = m_HumidityController.Control(m_HumidityInPercentage);
    if (humidityGeneratorState == STATE_ON)
    {
      bsp_humidity_motor_turn_on();
    }
    else
    {
      bsp_humidity_motor_turn_off();
    }
  }
}

auto Presenter::ControlHeater(void)
{
  const auto currentTimeStamp = bsp_get_time_in_ms();
  const auto timestampDiff    = currentTimeStamp - m_HeaterControlTimestamp;
  if (timestampDiff > 3000U)
  {
    m_HeaterControlTimestamp = currentTimeStamp;
  }
  if ((timestampDiff * 3U) > m_HeaterOnPeriod)
  {
    bsp_heater_turn_off();
  }
  else
  {
    bsp_heater_turn_on();
  }
}

void Presenter::Run(void)
{
  if (m_ModelUpdateTimerTask->IsFinished())
  {
    m_ModelUpdateTimerTask->Start();
    TimeInformationData timeInfoData;
    timeInfoData.m_CurrentTimestampInSecond = TimeUtils::TimeSettings::GetIncubatorTimeInSeconds();
    m_Model->Update(timeInfoData);
    m_View->UpdateTimeInformationData(timeInfoData);
  }
  ReadSensorsAndUpdateDisplay();
  ControlTemperature();
  ControlHumidity();
  ControlHeater();
}

} // namespace Incubator
