#include "Incubator/View/Screen/CurrentTimeSettingsScreen.h"

namespace Incubator
{

void CurrentTimeSettingsScreen::HandleScreenLineDay(const JoystickEvent &event)
{
  if (event.bIsLeftPressed)
  {
    SetNextScreen(SCREEN_TYPE_TIME_SETTINGS);
  }
  else if (event.bIsDownPressed)
  {
    m_SelectedLine = CURRENT_TIME_SETTINGS_SCREEN_LINE_HOUR;
    m_Lcd->MoveCursor(1U, 0U);
    m_Lcd->Print(" ");
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else if (event.bIsRightPressed || event.bIsButtonPressed)
  {
    SetNextScreen(SCREEN_TYPE_DATA_SET_CURRENT_DAY);
  }
  else
  {
    // intentionally left blank
  }
}

void CurrentTimeSettingsScreen::HandleScreenLineHour(const JoystickEvent &event)
{
  if (event.bIsLeftPressed)
  {
    SetNextScreen(SCREEN_TYPE_TIME_SETTINGS);
  }
  else if (event.bIsUpPressed)
  {
    m_SelectedLine = CURRENT_TIME_SETTINGS_SCREEN_LINE_DAY;
    m_Lcd->MoveCursor(1U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(" ");
  }
  else if (event.bIsDownPressed)
  {
    m_SelectedLine = CURRENT_TIME_SETTINGS_SCREEN_LINE_MINUTE;
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(" ");
    m_Lcd->MoveCursor(3U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else if (event.bIsRightPressed || event.bIsButtonPressed)
  {
    SetNextScreen(SCREEN_TYPE_DATA_SET_CURRENT_HOUR);
  }
  else
  {
    // intentionally left blank
  }
}

void CurrentTimeSettingsScreen::HandleScreenLineMinute(const JoystickEvent &event)
{
  if (event.bIsLeftPressed)
  {
    SetNextScreen(SCREEN_TYPE_TIME_SETTINGS);
  }
  else if (event.bIsUpPressed)
  {
    m_SelectedLine = CURRENT_TIME_SETTINGS_SCREEN_LINE_HOUR;
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
    m_Lcd->MoveCursor(3U, 0U);
    m_Lcd->Print(" ");
  }
  else if (event.bIsRightPressed || event.bIsButtonPressed)
  {
    SetNextScreen(SCREEN_TYPE_DATA_SET_CURRENT_MINUTE);
  }
  else
  {
    // intentionally left blank
  }
}

CurrentTimeSettingsScreen::CurrentTimeSettingsScreen()
    : AScreen{SCREEN_TYPE_CURRENT_TIME_SETTINGS}, m_Lcd{nullptr},
      m_SelectedLine{CURRENT_TIME_SETTINGS_SCREEN_LINE_DAY}
{
}

CurrentTimeSettingsScreen::~CurrentTimeSettingsScreen()
{
}

void CurrentTimeSettingsScreen::Initialize(Lcd2004 *tc2004Lcd)
{
  m_Lcd = tc2004Lcd;
}

void CurrentTimeSettingsScreen::OnInitial()
{
  Reset();
  m_Lcd->Clear();
  m_Lcd->MoveCursor(0U, 0U);
  m_Lcd->Print("[G");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_U);
  m_Lcd->Print("ncel Zaman]");
  m_Lcd->MoveCursor(1U, 0U);
  if (CURRENT_TIME_SETTINGS_SCREEN_LINE_DAY == m_SelectedLine)
  {
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else
  {
    m_Lcd->Print(" ");
  }
  m_Lcd->Print("G");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_U);
  m_Lcd->Print("n");

  m_Lcd->MoveCursor(2U, 0U);
  if (CURRENT_TIME_SETTINGS_SCREEN_LINE_HOUR == m_SelectedLine)
  {
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else
  {
    m_Lcd->Print(" ");
  }
  m_Lcd->Print("Saat");

  m_Lcd->MoveCursor(3U, 0U);
  if (CURRENT_TIME_SETTINGS_SCREEN_LINE_MINUTE == m_SelectedLine)
  {
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else
  {
    m_Lcd->Print(" ");
  }
  m_Lcd->Print("Dakika");
}

void CurrentTimeSettingsScreen::Run()
{
  // intentionally left blank
}

void CurrentTimeSettingsScreen::OnUserAction(const JoystickEvent &event)
{
  switch (m_SelectedLine)
  {
    case CURRENT_TIME_SETTINGS_SCREEN_LINE_DAY:
    {
      HandleScreenLineDay(event);
      break;
    }

    case CURRENT_TIME_SETTINGS_SCREEN_LINE_HOUR:
    {
      HandleScreenLineHour(event);
      break;
    }

    case CURRENT_TIME_SETTINGS_SCREEN_LINE_MINUTE:
    {
      HandleScreenLineMinute(event);
      break;
    }

    default:
      break;
  }
  // intentionally left blank
}

} // namespace Incubator
