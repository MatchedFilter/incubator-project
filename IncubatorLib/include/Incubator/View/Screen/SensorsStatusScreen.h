#ifndef INCUBATOR_SENSORSSTATUSSCREEN_H
#define INCUBATOR_SENSORSSTATUSSCREEN_H
#include "AScreen.h"
#include "Incubator/IncubatorData/SensorsStatusData.h"
#include "Incubator/Lcd2004.h"
#include "TimeUtils/MillisecondTimer.h"
namespace Incubator
{
enum EnumSensorsStatusScreenLine : uint8_t
{
  SENSOR_STATUS_SCREEN_LINE_SHT31,
  SENSOR_STATUS_SCREEN_LINE_NTC,
  SENSOR_STATUS_SCREEN_LINE_DHT11
};

class SensorsStatusScreen : public AScreen
{
public:
  SensorsStatusScreen();
  ~SensorsStatusScreen();
  void Initialize(Lcd2004 *tc2004Lcd);
  void OnInitial() override;

  virtual void Run() override;

  void OnUserAction(const JoystickEvent &event) override;
  void UpdateSensorsStatus(const SensorsStatusData &data);

private:
  Lcd2004 *m_Lcd;
  EnumSensorsStatusScreenLine m_SelectedLine;
  SensorsStatusData m_SensorsStatusData;
  TimeUtils::MillisecondTimer *m_SensorStatusScreenUpdateTimerTask;

private:
  void PrintSensorStatus(const EnumSensorStatus &sensorStatus);
};
} // namespace Incubator

#endif // INCUBATOR_SENSORSSTATUSSCREEN_H
