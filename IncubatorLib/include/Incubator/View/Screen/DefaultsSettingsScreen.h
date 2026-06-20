#ifndef INCUBATOR_DEFAULTSSETTINGSSCREEN_H
#define INCUBATOR_DEFAULTSSETTINGSSCREEN_H
#include "AScreen.h"
#include "Incubator/IncubatorData/SettingsData.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
#include "Incubator/Lcd2004.h"
#include "TimeUtils/MillisecondTimer.h"
namespace Incubator
{

enum EnumDefaultsSettingsScreenLine : uint8_t
{
  DEFAULTS_SETTINGS_SCREEN_LINE_CHICKEN,
  DEFAULTS_SETTINGS_SCREEN_LINE_GOOSE,
  DEFAULTS_SETTINGS_SCREEN_LINE_DUCK,
  DEFAULTS_SETTINGS_SCREEN_LINE_QUAIL,
  DEFAULTS_SETTINGS_SCREEN_LINE_SIZE
};

class DefaultsSettingsScreen : public AScreen
{
public:
  DefaultsSettingsScreen();
  ~DefaultsSettingsScreen();
  void Initialize(Lcd2004 *tc2004Lcd, SettingsData *changedSettingsData);
  void OnInitial() override;

  virtual void Run() override;

  void OnUserAction(const JoystickEvent &event) override;

private:
  Lcd2004 *m_Lcd;
  EnumDefaultsSettingsScreenLine m_SelectedLine;
  SettingsData *m_ChangedSettingsData;
  static constexpr uint8_t SCREEN_MAX_LINE_SIZE = 3U;

private:
  void HandleChickenLineEvent(const JoystickEvent &event);
  void HandleGooseLineEvent(const JoystickEvent &event);
  void HandleDuckLineEvent(const JoystickEvent &event);
  void HandleQuailLineEvent(const JoystickEvent &event);
  uint8_t DetermineStartLine() const;
  void PrintLine(const uint8_t lineNumber);
};
} // namespace Incubator

#endif // INCUBATOR_DEFAULTSSETTINGSSCREEN_H
