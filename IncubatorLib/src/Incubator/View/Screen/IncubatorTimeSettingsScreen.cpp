#include "Incubator/View/Screen/IncubatorTimeSettingsScreen.h"

namespace Incubator
{

void IncubatorTimeSettingsScreen::HandleScreenLineTotalDays(const JoystickEvent &event)
{
  if (event.bIsLeftPressed)
  {
    SetNextScreen(SCREEN_TYPE_TIME_SETTINGS);
  }
  else if (event.bIsDownPressed)
  {
    m_SelectedLine = INCUBATOR_TIME_SETTINGS_SCREEN_LINE_LAST_DAYS;
    m_Lcd->MoveCursor(1U, 0U);
    m_Lcd->Print(" ");
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else if (event.bIsRightPressed || event.bIsButtonPressed)
  {
    SetNextScreen(SCREEN_TYPE_DATA_SET_TOTAL_DAY_COUNT);
  }
  else
  {
    // intentionally left blank
  }
}

void IncubatorTimeSettingsScreen::HandleScreenLineLastDays(const JoystickEvent &event)
{
  if (event.bIsLeftPressed)
  {
    SetNextScreen(SCREEN_TYPE_TIME_SETTINGS);
  }
  else if (event.bIsUpPressed)
  {
    m_SelectedLine = INCUBATOR_TIME_SETTINGS_SCREEN_LINE_TOTAL_DAYS;
    m_Lcd->MoveCursor(1U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(" ");
  }
  else if (event.bIsRightPressed || event.bIsButtonPressed)
  {
    SetNextScreen(SCREEN_TYPE_DATA_SET_LAST_DAY_COUNT);
  }
  else
  {
    // intentionally left blank
  }
}

IncubatorTimeSettingsScreen::IncubatorTimeSettingsScreen()
    : AScreen{SCREEN_TYPE_INCUBATOR_TIME_SETTINGS}, m_Lcd{nullptr},
      m_SelectedLine{INCUBATOR_TIME_SETTINGS_SCREEN_LINE_TOTAL_DAYS}
{
}

IncubatorTimeSettingsScreen::~IncubatorTimeSettingsScreen()
{
}

void IncubatorTimeSettingsScreen::Initialize(Lcd2004 *tc2004Lcd)
{
  m_Lcd = tc2004Lcd;
}

void IncubatorTimeSettingsScreen::OnInitial()
{
  Reset();
  m_Lcd->Clear();
  m_Lcd->MoveCursor(0U, 0U);
  m_Lcd->Print("[Kulu");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_C);
  m_Lcd->Print("ka Zaman]");
  m_Lcd->MoveCursor(1U, 0U);
  if (INCUBATOR_TIME_SETTINGS_SCREEN_LINE_TOTAL_DAYS == m_SelectedLine)
  {
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else
  {
    m_Lcd->Print(" ");
  }
  m_Lcd->Print("Toplam G");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_U);
  m_Lcd->Print("n Say");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
  m_Lcd->Print("s");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);

  m_Lcd->MoveCursor(2U, 0U);
  if (INCUBATOR_TIME_SETTINGS_SCREEN_LINE_LAST_DAYS == m_SelectedLine)
  {
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else
  {
    m_Lcd->Print(" ");
  }
  m_Lcd->Print("Son G");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_U);
  m_Lcd->Print("n Say");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
  m_Lcd->Print("s");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
}

void IncubatorTimeSettingsScreen::Run()
{
  // intentionally left blank
}

void IncubatorTimeSettingsScreen::OnUserAction(const JoystickEvent &event)
{
  switch (m_SelectedLine)
  {
    case INCUBATOR_TIME_SETTINGS_SCREEN_LINE_TOTAL_DAYS:
    {
      HandleScreenLineTotalDays(event);
      break;
    }

    case INCUBATOR_TIME_SETTINGS_SCREEN_LINE_LAST_DAYS:
    {
      HandleScreenLineLastDays(event);
      break;
    }

    default:
      break;
  }
  // intentionally left blank
}

} // namespace Incubator
