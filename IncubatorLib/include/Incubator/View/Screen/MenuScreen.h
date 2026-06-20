#ifndef INCUBATOR_MENUSCREEN_H
#define INCUBATOR_MENUSCREEN_H
#include "AScreen.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
#include "Incubator/Lcd2004.h"
#include "TimeUtils/MillisecondTimer.h"
namespace Incubator
{

enum EnumMenuScreenLine : uint8_t
{
  MENU_SCREEN_LINE_SETTINGS,
  MENU_SCREEN_LINE_SENSORS_STATUS
};

class MenuScreen : public AScreen
{
public:
  MenuScreen();
  ~MenuScreen();
  void Initialize(Lcd2004 *tc2004Lcd);
  void OnInitial() override;
  inline EnumMenuScreenLine GetMenuScreenLine() const
  {
    return m_SelectedLine;
  }

  virtual void Run() override;

  void OnUserAction(const JoystickEvent &event) override;

private:
  Lcd2004 *m_Lcd;
  EnumMenuScreenLine m_SelectedLine;

private:
  void HandleScreenLineSettings(const JoystickEvent &event);
  void HandleScreenLineSensorsStatus(const JoystickEvent &event);
};
} // namespace Incubator

#endif // INCUBATOR_MENUSCREEN_H
