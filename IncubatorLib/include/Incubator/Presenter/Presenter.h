#ifndef INCUBATOR_PRESENTER_H
#define INCUBATOR_PRESENTER_H
#include "Incubator/Controller/HumidityController.h"
#include "Incubator/Controller/TemperatureController.h"
#include "Incubator/IncubatorData/AdminData.h"
#include "Incubator/Model/IModel.h"
#include "Incubator/View/DataChangedEventHandler/IAdminDataChangedEventHandler.h"
#include "Incubator/View/DataChangedEventHandler/ISettingsDataChangedEventHandler.h"
#include "Incubator/View/DataChangedEventHandler/ITimeInformationDataChangedEventHandler.h"
#include "Incubator/View/IView.h"
#include "TimeUtils/MillisecondTimer.h"

namespace Incubator
{
class Presenter : public IAdminDataChangedEventHandler,
                  ISettingsDataChangedEventHandler,
                  ITimeInformationDataChangedEventHandler
{
public:
  Presenter();
  ~Presenter();
  void Initialize(IView *view, IModel *model);

  bool GetSettingsData(SettingsData &data) const;
  bool GetPidData(double &p, double &i, double &d) const;
  bool GetHumidityHysterisisDiff(uint8_t &upperDiff, uint8_t &lowerDiff) const;

  virtual void OnUpdate(const AdminData &data) override;
  virtual void OnUpdate(const SettingsData &data) override;
  virtual void OnUpdate(const TimeInformationData &data) override;

  void Run(void);

private:
  IView *m_View;
  IModel *m_Model;
  bool m_bIsInitialized;
  AdminData m_AdminData;
  SettingsData m_SettingsData;
  TimeUtils::MillisecondTimer *m_ModelUpdateTimerTask;
  HumidityController m_HumidityController;
  TemperatureController m_TemperatureController;
  TimeUtils::MillisecondTimer *m_SensorReadingTimer;
  TimeUtils::MillisecondTimer *m_TemperatureControllerTimer;
  TimeUtils::MillisecondTimer *m_HumidityControllerTimer;
  SensorsStatusData m_SensorsStatusData;
  uint8_t m_HumidityInPercentage;
  int32_t m_TemperatureInMilliCelcius;
  uint64_t m_PreviousPidTimestamp;
  uint16_t m_HeaterOnPeriod;
  uint64_t m_HeaterControlTimestamp;

private:
  static bool ReadModel(IModel *model, AdminData &pid, SettingsData &settings,
                        TimeInformationData &timeInformation);
  static bool UpdateModel(IModel *model, AdminData &data);
  static bool UpdateModel(IModel *model, SettingsData &data);
  static bool UpdateModel(IModel *model, TimeInformationData &data);
  bool SyncModels(AdminData &pid, SettingsData &settings, TimeInformationData &timeInformation);
  auto ReadSensorsAndUpdateDisplay(void);
  auto ControlTemperature(void);
  auto ControlHumidity(void);
  auto ControlHeater(void);
};
} // namespace Incubator

#endif // INCUBATOR_PRESENTER_H
