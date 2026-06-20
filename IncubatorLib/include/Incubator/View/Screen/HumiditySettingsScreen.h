#ifndef INCUBATOR_HUMIDITYSETTINGSSCREEN_H
#define INCUBATOR_HUMIDITYSETTINGSSCREEN_H
#include "AScreen.h"
#include "Incubator/IncubatorData/SettingsData.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
#include "Incubator/Lcd2004.h"
#include "TimeUtils/MillisecondTimer.h"
namespace Incubator
{

enum EnumHumiditySettingsScreenLine : uint8_t
{
  HUMIDITY_SETTINGS_SCREEN_LINE_HUMIDITY,
  HUMIDITY_SETTINGS_SCREEN_LINE_LAST_DAYS_HUMIDITY,
};

class HumiditySettingsScreen : public AScreen
{
public:
  HumiditySettingsScreen();
  ~HumiditySettingsScreen();
  void Initialize(Lcd2004 *tc2004Lcd);
  void OnInitial() override;
  virtual void Run() override;
  void OnUserAction(const JoystickEvent &event) override;

private:
  Lcd2004 *m_Lcd;
  EnumHumiditySettingsScreenLine m_SelectedLine;

private:
  void HandlerHumidityLine(const JoystickEvent &event);
  void HandleHumidityLastDaysHumidityLine(const JoystickEvent &event);
};
} // namespace Incubator

#endif // INCUBATOR_HUMIDITYSETTINGSSCREEN_H
