#include "Incubator/View/Screen/TimeSettingsScreen.h"

#include "bsp_config.h"

namespace Incubator
{

void TimeSettingsScreen::HandleScreenLineReset(const JoystickEvent &event)
{
  if (event.bIsLeftPressed)
  {
    SetNextScreen(SCREEN_TYPE_SETTINGS);
  }
  else if (event.bIsDownPressed)
  {
    m_SelectedLine = TIME_SETTINGS_SCREEN_LINE_CURRENT_TIME;
    m_Lcd->MoveCursor(1U, 0U);
    m_Lcd->Print(" ");
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else if (event.bIsRightPressed || event.bIsButtonPressed)
  {
    m_ChangedTimeInformationData->m_CurrentTimestampInSecond = static_cast<uint32_t>(0UL);
    SetNextScreen(SCREEN_TYPE_QUESTION_TIME_RESET);
  }
  else
  {
    // intentionally left blank
  }
}

void TimeSettingsScreen::HandleScreenLineCurrentTime(const JoystickEvent &event)
{
  if (event.bIsLeftPressed)
  {
    SetNextScreen(SCREEN_TYPE_SETTINGS);
  }
  else if (event.bIsUpPressed)
  {
    m_SelectedLine = TIME_SETTINGS_SCREEN_LINE_RESET;
    m_Lcd->MoveCursor(1U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(" ");
  }
  else if (event.bIsDownPressed)
  {
    m_SelectedLine = TIME_SETTINGS_SCREEN_LINE_INCUBATOR_TIME;
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(" ");
    m_Lcd->MoveCursor(3U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else if (event.bIsRightPressed || event.bIsButtonPressed)
  {
    SetNextScreen(SCREEN_TYPE_CURRENT_TIME_SETTINGS);
  }
  else
  {
    // intentionally left blank
  }
}

void TimeSettingsScreen::HandleScreenLineIncubatorTime(const JoystickEvent &event)
{
  if (event.bIsLeftPressed)
  {
    SetNextScreen(SCREEN_TYPE_SETTINGS);
  }
  else if (event.bIsUpPressed)
  {
    m_SelectedLine = TIME_SETTINGS_SCREEN_LINE_CURRENT_TIME;
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
    m_Lcd->MoveCursor(3U, 0U);
    m_Lcd->Print(" ");
  }
  else if (event.bIsRightPressed || event.bIsButtonPressed)
  {
    SetNextScreen(SCREEN_TYPE_INCUBATOR_TIME_SETTINGS);
  }
  else
  {
    // intentionally left blank
  }
}

TimeSettingsScreen::TimeSettingsScreen()
    : AScreen{SCREEN_TYPE_TIME_SETTINGS}, m_Lcd{nullptr},
      m_SelectedLine{TIME_SETTINGS_SCREEN_LINE_RESET}, m_ChangedTimeInformationData{nullptr}
{
}

TimeSettingsScreen::~TimeSettingsScreen()
{
}

void TimeSettingsScreen::Initialize(Lcd2004 *tc2004Lcd,
                                    TimeInformationData *changedTimeInformationData)
{
  m_Lcd                        = tc2004Lcd;
  m_ChangedTimeInformationData = changedTimeInformationData;
  bsp_assert(nullptr != m_ChangedTimeInformationData);
}

void TimeSettingsScreen::OnInitial()
{
  Reset();
  m_Lcd->Clear();
  m_Lcd->MoveCursor(0U, 0U);
  m_Lcd->Print("[Zaman Ayarlar");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
  m_Lcd->Print("]");
  m_Lcd->MoveCursor(1U, 0U);
  if (TIME_SETTINGS_SCREEN_LINE_RESET == m_SelectedLine)
  {
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else
  {
    m_Lcd->Print(" ");
  }
  m_Lcd->Print("S");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
  m_Lcd->Print("f");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
  m_Lcd->Print("rla");

  m_Lcd->MoveCursor(2U, 0U);
  if (TIME_SETTINGS_SCREEN_LINE_CURRENT_TIME == m_SelectedLine)
  {
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else
  {
    m_Lcd->Print(" ");
  }
  m_Lcd->Print("G");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_U);
  m_Lcd->Print("ncel Zaman");

  m_Lcd->MoveCursor(3U, 0U);
  if (TIME_SETTINGS_SCREEN_LINE_INCUBATOR_TIME == m_SelectedLine)
  {
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else
  {
    m_Lcd->Print(" ");
  }
  m_Lcd->Print("Kulu");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_C);
  m_Lcd->Print("ka Zaman");
}

void TimeSettingsScreen::Run()
{
  // intentionally left blank
}

void TimeSettingsScreen::OnUserAction(const JoystickEvent &event)
{
  switch (m_SelectedLine)
  {
    case TIME_SETTINGS_SCREEN_LINE_RESET:
    {
      HandleScreenLineReset(event);
      break;
    }

    case TIME_SETTINGS_SCREEN_LINE_CURRENT_TIME:
    {
      HandleScreenLineCurrentTime(event);
      break;
    }

    case TIME_SETTINGS_SCREEN_LINE_INCUBATOR_TIME:
    {
      HandleScreenLineIncubatorTime(event);
      break;
    }

    default:
      break;
  }
  // intentionally left blank
}

} // namespace Incubator
