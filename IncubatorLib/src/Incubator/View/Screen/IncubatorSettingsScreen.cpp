#include "Incubator/View/Screen/IncubatorSettingsScreen.h"

namespace Incubator
{

void IncubatorSettingsScreen::HandleIncubatorSettingsLine(const JoystickEvent &event)
{
  if (event.bIsLeftPressed)
  {
    SetNextScreen(SCREEN_TYPE_SETTINGS);
  }
  else if (event.bIsDownPressed)
  {
    m_SelectedLine = INCUBATOR_SETTINGS_SCREEN_LINE_TEMPERATURE;
    m_Lcd->MoveCursor(1U, 0U);
    m_Lcd->Print(" ");
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else if (event.bIsRightPressed || event.bIsButtonPressed)
  {
    SetNextScreen(SCREEN_TYPE_DEFAULTS_SETTINGS);
  }
  else
  {
    // intentionally left blank
  }
}

void IncubatorSettingsScreen::HandleTemperatureSettingsLine(const JoystickEvent &event)
{
  if (event.bIsLeftPressed)
  {
    SetNextScreen(SCREEN_TYPE_SETTINGS);
  }
  else if (event.bIsUpPressed)
  {
    m_SelectedLine = INCUBATOR_SETTINGS_SCREEN_LINE_DEFAULT;
    m_Lcd->MoveCursor(1U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(" ");
  }
  else if (event.bIsDownPressed)
  {
    m_SelectedLine = INCUBATOR_SETTINGS_SCREEN_LINE_HUMIDITY;
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(" ");
    m_Lcd->MoveCursor(3U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else if (event.bIsRightPressed || event.bIsButtonPressed)
  {
    SetNextScreen(SCREEN_TYPE_TEMPERATURE_SETTINGS);
  }
  else
  {
    // intentionally left blank
  }
}

void IncubatorSettingsScreen::HandleHumiditySettingsLine(const JoystickEvent &event)
{
  if (event.bIsLeftPressed)
  {
    SetNextScreen(SCREEN_TYPE_SETTINGS);
  }
  else if (event.bIsUpPressed)
  {
    m_SelectedLine = INCUBATOR_SETTINGS_SCREEN_LINE_TEMPERATURE;
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
    m_Lcd->MoveCursor(3U, 0U);
    m_Lcd->Print(" ");
  }
  else if (event.bIsRightPressed || event.bIsButtonPressed)
  {
    SetNextScreen(SCREEN_TYPE_HUMIDITY_SETTINGS);
  }
  else
  {
    // intentionally left blank
  }
}

IncubatorSettingsScreen::IncubatorSettingsScreen()
    : AScreen{SCREEN_TYPE_INCUBATOR_SETTINGS}, m_Lcd{nullptr},
      m_SelectedLine{INCUBATOR_SETTINGS_SCREEN_LINE_DEFAULT}
{
}

IncubatorSettingsScreen::~IncubatorSettingsScreen()
{
}

void IncubatorSettingsScreen::Initialize(Lcd2004 *tc2004Lcd)
{
  m_Lcd = tc2004Lcd;
}

void IncubatorSettingsScreen::OnInitial()
{
  Reset();
  m_Lcd->Clear();
  m_Lcd->MoveCursor(0U, 0U);
  m_Lcd->Print("[Kulu");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_C);
  m_Lcd->Print("ka Ayarlar");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
  m_Lcd->Print("]");
  m_Lcd->MoveCursor(1U, 0U);
  if (INCUBATOR_SETTINGS_SCREEN_LINE_DEFAULT == m_SelectedLine)
  {
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else
  {
    m_Lcd->Print(" ");
  }
  m_Lcd->Print("Varsay");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
  m_Lcd->Print("lanlar");

  m_Lcd->MoveCursor(2U, 0U);
  if (INCUBATOR_SETTINGS_SCREEN_LINE_TEMPERATURE == m_SelectedLine)
  {
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else
  {
    m_Lcd->Print(" ");
  }
  m_Lcd->Print("S");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
  m_Lcd->Print("cakl");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
  m_Lcd->Print("k");

  m_Lcd->MoveCursor(3U, 0U);
  if (INCUBATOR_SETTINGS_SCREEN_LINE_HUMIDITY == m_SelectedLine)
  {
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else
  {
    m_Lcd->Print(" ");
  }
  m_Lcd->Print("Nem");
}

void IncubatorSettingsScreen::Run()
{
  // intentionally left blank
}

void IncubatorSettingsScreen::OnUserAction(const JoystickEvent &event)
{
  switch (m_SelectedLine)
  {
    case INCUBATOR_SETTINGS_SCREEN_LINE_DEFAULT:
    {
      HandleIncubatorSettingsLine(event);
      break;
    }

    case INCUBATOR_SETTINGS_SCREEN_LINE_TEMPERATURE:
    {
      HandleTemperatureSettingsLine(event);
      break;
    }

    case INCUBATOR_SETTINGS_SCREEN_LINE_HUMIDITY:
    {
      HandleHumiditySettingsLine(event);
      break;
    }

    default:
      break;
  }
}

} // namespace Incubator
