#include "Incubator/Presenter/Presenter.h"

#include "TimeUtils/TimeSettings.h"
#include "TimeUtils/TimerManager.h"

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
    (void) UpdateModel(m_Model, pid);
    (void) UpdateModel(m_Model, settings);
    (void) UpdateModel(m_Model, timeInformation);
  }
  return bResult;
}

Presenter::Presenter()
    : m_View{nullptr}, m_Model{nullptr}, m_bIsInitialized{false}, m_ModelUpdateTimerTask{nullptr}
{
}

Presenter::~Presenter()
{
}

void Presenter::Initialize(IView *view, IModel *model)
{
  m_View  = view;
  m_Model = model;

  m_AdminDataCache.Initialize(m_Model, m_View);
  m_SettingsDataCache.Initialize(m_Model, m_View);
  m_TimeInformationDataChangedEventHandler.Initialize(m_Model, m_View);
  m_ModelUpdateTimerTask = TimeUtils::TimerManager::CreateMillisecondTimer();

  DataChangedEventHandlers eventHandlers;
  eventHandlers.Reset();
  eventHandlers.m_AdminDataChangedEventHandler    = &m_AdminDataCache;
  eventHandlers.m_SettingsDataChangedEventHandler = &m_SettingsDataCache;
  eventHandlers.m_TimeInformationDataChangedEventHandler =
    &m_TimeInformationDataChangedEventHandler;

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

      m_SettingsDataCache.OnUpdate(settings);
      m_AdminDataCache.OnUpdate(adminSettings);
    }
    else
    {
      m_View->OnModelFailure();
    }
  }
}

void Presenter::UpdateTemperature(const int32_t &temperatureInMilliCelcius)
{
  m_View->UpdateTemperature(temperatureInMilliCelcius);
}

void Presenter::UpdateHumidity(const uint8_t humidityInPercent)
{
  m_View->UpdateHumidity(humidityInPercent);
}

void Presenter::OnTemperatureFailure()
{
  m_View->OnTemperatureFailure();
}

void Presenter::OnHumidityFailure()
{
  m_View->OnHumidityFailure();
}

void Presenter::UpdateSensorsStatus(const SensorsStatusData &data)
{
  m_View->UpdateSensorsStatus(data);
}

bool Presenter::GetSettingsData(SettingsData &data) const
{
  return m_SettingsDataCache.GetSettingsData(data);
}

bool Presenter::GetPidData(double &p, double &i, double &d) const
{
  return m_AdminDataCache.GetPid(p, i, d);
}

bool Presenter::GetHumidityHysterisisDiff(uint8_t &upperDiff, uint8_t &lowerDiff) const
{
  return m_AdminDataCache.GetHumidityHysterisisDiff(upperDiff, lowerDiff);
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
}

} // namespace Incubator
