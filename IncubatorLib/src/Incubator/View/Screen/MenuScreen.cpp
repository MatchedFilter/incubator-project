#include "Incubator/View/Screen/MenuScreen.h"

namespace Incubator
{

void MenuScreen::HandleScreenLineSettings(const JoystickEvent &event)
{
  if (event.bIsLeftPressed)
  {
    SetNextScreen(SCREEN_TYPE_MAIN);
  }
  else if (event.bIsDownPressed)
  {
    m_SelectedLine = MENU_SCREEN_LINE_SENSORS_STATUS;
    m_Lcd->MoveCursor(1U, 0U);
    m_Lcd->Print(" ");
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else if (event.bIsRightPressed || event.bIsButtonPressed)
  {
    SetNextScreen(SCREEN_TYPE_SETTINGS);
  }
  else
  {
    // intentionally left blank
  }
}

void MenuScreen::HandleScreenLineSensorsStatus(const JoystickEvent &event)
{
  if (event.bIsLeftPressed)
  {
    SetNextScreen(SCREEN_TYPE_MAIN);
  }
  else if (event.bIsUpPressed)
  {
    m_SelectedLine = MENU_SCREEN_LINE_SETTINGS;
    m_Lcd->MoveCursor(1U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(" ");
  }
  else if (event.bIsRightPressed || event.bIsButtonPressed)
  {
    SetNextScreen(SCREEN_TYPE_SENSORS_STATUS);
  }
  else
  {
    // intentionally left blank
  }
}

MenuScreen::MenuScreen()
    : AScreen{SCREEN_TYPE_MENU}, m_Lcd{nullptr}, m_SelectedLine{MENU_SCREEN_LINE_SETTINGS}
{
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::Initialize(Lcd2004 *tc2004Lcd)
{
  m_Lcd = tc2004Lcd;
}

void MenuScreen::OnInitial()
{
  Reset();
  m_Lcd->Clear();
  m_Lcd->MoveCursor(0U, 0U);
  m_Lcd->Print("[Men");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_U);
  m_Lcd->Print("]");
  m_Lcd->MoveCursor(1U, 0U);
  if (MENU_SCREEN_LINE_SETTINGS == m_SelectedLine)
  {
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else
  {
    m_Lcd->Print(" ");
  }
  m_Lcd->Print("Ayarlar");

  m_Lcd->MoveCursor(2U, 0U);
  if (MENU_SCREEN_LINE_SENSORS_STATUS == m_SelectedLine)
  {
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else
  {
    m_Lcd->Print(" ");
  }
  m_Lcd->Print("Sens");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_O);
  m_Lcd->Print("r Durumlar");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
}

void MenuScreen::Run()
{
  // intentionally left blank
}

void MenuScreen::OnUserAction(const JoystickEvent &event)
{
  switch (m_SelectedLine)
  {
    case MENU_SCREEN_LINE_SETTINGS:
    {
      HandleScreenLineSettings(event);
      break;
    }

    case MENU_SCREEN_LINE_SENSORS_STATUS:
    {
      HandleScreenLineSensorsStatus(event);
      break;
    }

    default:
      break;
  }
}

} // namespace Incubator
