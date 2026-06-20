#ifndef INCUBATOR_PRESENTER_H
#define INCUBATOR_PRESENTER_H
#include "Incubator/Model/IModel.h"
#include "Incubator/Presenter/DataChangedEventHandlers/AdminDataCache.h"
#include "Incubator/Presenter/DataChangedEventHandlers/SettingsDataCache.h"
#include "Incubator/Presenter/DataChangedEventHandlers/TimeInformationDataChangedEventHandler.h"
#include "Incubator/View/IView.h"
#include "TimeUtils/MillisecondTimer.h"

namespace Incubator
{
class Presenter
{
public:
  Presenter();
  ~Presenter();
  void Initialize(IView *view, IModel *model);

  void UpdateTemperature(const double &temperatureInCelcius);
  void UpdateHumidity(const uint8_t humidityInPercent);

  void OnTemperatureFailure();
  void OnHumidityFailure();
  void UpdateSensorsStatus(const SensorsStatusData &data);
  bool GetSettingsData(SettingsData &data) const;
  bool GetPidData(double &p, double &i, double &d) const;
  bool GetHumidityHysterisisDiff(uint8_t &upperDiff, uint8_t &lowerDiff) const;

  void Run(void);

private:
  IView *m_View;
  IModel *m_Model;
  bool m_bIsInitialized;
  AdminDataCache m_AdminDataCache;
  SettingsDataCache m_SettingsDataCache;
  TimeInformationDataChangedEventHandler m_TimeInformationDataChangedEventHandler;
  SettingsData m_SettingsData;
  TimeUtils::MillisecondTimer *m_ModelUpdateTimerTask;

private:
  static bool ReadModel(IModel *model, AdminData &pid, SettingsData &settings,
                        TimeInformationData &timeInformation);
  static bool UpdateModel(IModel *model, AdminData &data);
  static bool UpdateModel(IModel *model, SettingsData &data);
  static bool UpdateModel(IModel *model, TimeInformationData &data);
  bool SyncModels(AdminData &pid, SettingsData &settings, TimeInformationData &timeInformation);
};
} // namespace Incubator

#endif // INCUBATOR_PRESENTER_H
