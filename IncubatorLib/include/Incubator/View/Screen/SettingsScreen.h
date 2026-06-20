#ifndef INCUBATOR_SETTINGSSCREEN_H
#define INCUBATOR_SETTINGSSCREEN_H
#include "AScreen.h"
#include "Incubator/IncubatorData/SettingsData.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
#include "Incubator/Lcd2004.h"
#include "TimeUtils/MillisecondTimer.h"
namespace Incubator
{

enum EnumSettingsScreenLine : uint8_t
{
  SETTINGS_SCREEN_LINE_INCUBATOR,
  SETTINGS_SCREEN_LINE_TIME,
  SETTINGS_SCREEN_LINE_ADMINISTRATOR,

};

enum EnumAdministratorEnterLevel : uint8_t
{
  ADMINISTRATOR_ENTER_LEVEL_0,
  ADMINISTRATOR_ENTER_LEVEL_1,
  ADMINISTRATOR_ENTER_LEVEL_2,
};

class SettingsScreen : public AScreen
{
public:
  SettingsScreen();
  ~SettingsScreen();
  void Initialize(Lcd2004 *tc2004Lcd);
  void OnInitial() override;
  inline EnumSettingsScreenLine GetSettingsScreenLine() const
  {
    return m_SelectedLine;
  }

  virtual void Run() override;

  void OnUserAction(const JoystickEvent &event) override;

private:
  Lcd2004 *m_Lcd;
  EnumSettingsScreenLine m_SelectedLine;
  static constexpr uint32_t ADMINISTRATOR_CLICK_TIMEOUT_IN_MILLISECOND =
    static_cast<uint32_t>(500UL);
  EnumAdministratorEnterLevel m_AdministratorEnterLevel;
  TimeUtils::MillisecondTimer *m_AdministratorClickTimerTask;

private:
  void HandleScreenLineIncubator(const JoystickEvent &event);
  void HandleScreenLineTime(const JoystickEvent &event);
  void HandleScreenLineAdministrator(const JoystickEvent &event);
};
} // namespace Incubator

#endif // INCUBATOR_SETTINGSSCREEN_H
