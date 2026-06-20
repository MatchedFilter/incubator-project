#ifndef INCUBATOR_TIMESETTINGSSCREEN_H
#define INCUBATOR_TIMESETTINGSSCREEN_H
#include "AScreen.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
#include "Incubator/Lcd2004.h"
#include "TimeUtils/MillisecondTimer.h"
namespace Incubator
{

enum EnumTimeSettingsScreenLine : uint8_t
{
  TIME_SETTINGS_SCREEN_LINE_RESET,
  TIME_SETTINGS_SCREEN_LINE_CURRENT_TIME,
  TIME_SETTINGS_SCREEN_LINE_INCUBATOR_TIME
};

class TimeSettingsScreen : public AScreen
{
public:
  TimeSettingsScreen();
  ~TimeSettingsScreen();
  void Initialize(Lcd2004 *tc2004Lcd, TimeInformationData *changedTimeInformationData);
  void OnInitial() override;

  virtual void Run() override;

  void OnUserAction(const JoystickEvent &event) override;

private:
  Lcd2004 *m_Lcd;
  EnumTimeSettingsScreenLine m_SelectedLine;
  TimeInformationData *m_ChangedTimeInformationData;

private:
  void HandleScreenLineReset(const JoystickEvent &event);
  void HandleScreenLineCurrentTime(const JoystickEvent &event);
  void HandleScreenLineIncubatorTime(const JoystickEvent &event);
};
} // namespace Incubator

#endif // INCUBATOR_TIMESETTINGSSCREEN_H
