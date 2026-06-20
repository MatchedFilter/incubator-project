#ifndef INCUBATOR_LCD2004VIEW_H
#define INCUBATOR_LCD2004VIEW_H
#include "IView.h"
#include "Incubator/Lcd2004.h"
#include "Incubator/View/JoystickEvent.h"
#include "Screen/ScreenFacade.h"
#include "TimeUtils/MillisecondTimer.h"

namespace Incubator
{
class Lcd2004View : public IView
{
public:
  Lcd2004View();
  ~Lcd2004View();
  virtual bool Initialize(const DataChangedEventHandlers *eventHandlers) override;
  virtual void UpdateTemperature(const int32_t temperatureInMilliCelcius) override;
  virtual void OnTemperatureFailure() override;

  virtual void UpdateHumidity(const uint8_t humidityInPercentage) override;
  virtual void OnHumidityFailure() override;

  virtual void UpdateAdminData(const AdminData &data) override;
  virtual void UpdateSettingsData(const SettingsData &data) override;
  virtual void UpdateTimeInformationData(const TimeInformationData &data) override;
  virtual void OnModelFailure() override;
  virtual void UpdateSensorsStatus(const SensorsStatusData &data) override;

  void Run();

private:
  Lcd2004 m_TC2004Lcd;
  bool m_bUpShifted;
  bool m_bDownShifted;
  bool m_bRightShifted;
  bool m_bLeftShifted;
  bool m_bSwitchPressed;
  ScreenFacade m_ScreenFacade;
  TimeUtils::MillisecondTimer *m_JoystickSensorTimerTask;

private:
  void ReadJoystick();
  void OnUserAction(const JoystickEvent event);
};
} // namespace Incubator

#endif // INCUBATOR_LCD2004VIEW_H
