#ifndef INCUBATOR_TemperaturePidSettingsScreen_H
#define INCUBATOR_TemperaturePidSettingsScreen_H
#include "AScreen.h"
#include "Incubator/Lcd2004.h"
namespace Incubator
{

enum EnumTemperaturePidSettingsScreenLine : uint8_t
{
  TEMPERATURE_PID_SETTINGS_SCREEN_LINE_P,
  TEMPERATURE_PID_SETTINGS_SCREEN_LINE_I,
  TEMPERATURE_PID_SETTINGS_SCREEN_LINE_D
};

class TemperaturePidSettingsScreen : public AScreen
{
public:
  TemperaturePidSettingsScreen();
  ~TemperaturePidSettingsScreen();
  void Initialize(Lcd2004 *tc2004Lcd);
  void OnInitial() override;

  virtual void Run() override;

  void OnUserAction(const JoystickEvent &event) override;

private:
  Lcd2004 *m_Lcd;
  EnumTemperaturePidSettingsScreenLine m_SelectedLine;

private:
  void HandleScreenLineP(const JoystickEvent &event);
  void HandleScreenLineI(const JoystickEvent &event);
  void HandleScreenLineD(const JoystickEvent &event);
};
} // namespace Incubator

#endif // INCUBATOR_TemperaturePidSettingsScreen_H
