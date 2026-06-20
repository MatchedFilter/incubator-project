#include "Incubator/View/Screen/DefaultsSettingsScreen.h"

#include "bsp_config.h"

namespace Incubator
{

constexpr uint8_t DefaultsSettingsScreen::SCREEN_MAX_LINE_SIZE;

void DefaultsSettingsScreen::HandleChickenLineEvent(const JoystickEvent &event)
{
  if (event.bIsLeftPressed)
  {
    SetNextScreen(SCREEN_TYPE_INCUBATOR_SETTINGS);
  }
  else if (event.bIsDownPressed)
  {
    m_SelectedLine = DEFAULTS_SETTINGS_SCREEN_LINE_GOOSE;
    m_Lcd->MoveCursor(1U, 0U);
    m_Lcd->Print(" ");
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else if (event.bIsRightPressed || event.bIsButtonPressed)
  {
    SetNextScreen(SCREEN_TYPE_QUESTION_SAVE);
    m_Lcd->Clear();
    m_Lcd->MoveCursor(1U, 0U);
    m_Lcd->Print("Se");
    m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_C);
    m_Lcd->Print("ilen: Tavuk");
    m_ChangedSettingsData->Reset();
  }
  else
  {
    // intentionally left blank
  }
}

void DefaultsSettingsScreen::HandleGooseLineEvent(const JoystickEvent &event)
{
  if (event.bIsLeftPressed)
  {
    SetNextScreen(SCREEN_TYPE_INCUBATOR_SETTINGS);
  }
  else if (event.bIsUpPressed)
  {
    m_SelectedLine = DEFAULTS_SETTINGS_SCREEN_LINE_CHICKEN;
    m_Lcd->MoveCursor(1U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(" ");
  }
  else if (event.bIsDownPressed)
  {
    m_SelectedLine = DEFAULTS_SETTINGS_SCREEN_LINE_DUCK;
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(" ");
    m_Lcd->MoveCursor(3U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else if (event.bIsRightPressed || event.bIsButtonPressed)
  {
    SetNextScreen(SCREEN_TYPE_QUESTION_SAVE);
    m_Lcd->Clear();
    m_Lcd->MoveCursor(1U, 0U);
    m_Lcd->Print("Se");
    m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_C);
    m_Lcd->Print("ilen: Kaz");
    m_ChangedSettingsData->m_TemperatureInMilliCelcius         = static_cast<uint32_t>(37700UL);
    m_ChangedSettingsData->m_LastDaysTemperatureInMilliCelcius = static_cast<uint32_t>(37000UL);
    m_ChangedSettingsData->m_HumidityInPercentage              = 60U;
    m_ChangedSettingsData->m_LastDaysHumidityInPercentage      = 70U;
    m_ChangedSettingsData->m_TotalIncubationDayCount           = 28U;
    m_ChangedSettingsData->m_LastDaysCount                     = 3U;
  }
  else
  {
    // intentionally left blank
  }
}

void DefaultsSettingsScreen::HandleDuckLineEvent(const JoystickEvent &event)
{
  if (event.bIsLeftPressed)
  {
    SetNextScreen(SCREEN_TYPE_INCUBATOR_SETTINGS);
  }
  else if (event.bIsUpPressed)
  {
    m_SelectedLine = DEFAULTS_SETTINGS_SCREEN_LINE_GOOSE;
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
    m_Lcd->MoveCursor(3U, 0U);
    m_Lcd->Print(" ");
  }
  else if (event.bIsDownPressed)
  {
    m_SelectedLine = DEFAULTS_SETTINGS_SCREEN_LINE_QUAIL;
    m_Lcd->MoveCursor(1U, 0U);
    m_Lcd->Print(" Kaz    ");
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(" ");
    m_Lcd->Print(BSP_LCD_2004_CHAR_UPPER_O);
    m_Lcd->Print("rdek    ");
    m_Lcd->MoveCursor(3U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
    m_Lcd->Print("B");
    m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
    m_Lcd->Print("ld");
    m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
    m_Lcd->Print("rc");
    m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
    m_Lcd->Print("n");
  }
  else if (event.bIsRightPressed || event.bIsButtonPressed)
  {
    SetNextScreen(SCREEN_TYPE_QUESTION_SAVE);
    m_Lcd->Clear();
    m_Lcd->MoveCursor(1U, 0U);
    m_Lcd->Print("Se");
    m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_C);
    m_Lcd->Print("ilen: ");
    m_Lcd->Print(BSP_LCD_2004_CHAR_UPPER_O);
    m_Lcd->Print("rdek");
    m_ChangedSettingsData->m_TemperatureInMilliCelcius         = static_cast<uint32_t>(37500UL);
    m_ChangedSettingsData->m_LastDaysTemperatureInMilliCelcius = static_cast<uint32_t>(37100UL);
    m_ChangedSettingsData->m_HumidityInPercentage              = 65U;
    m_ChangedSettingsData->m_LastDaysHumidityInPercentage      = 75U;
    m_ChangedSettingsData->m_TotalIncubationDayCount           = 28U;
    m_ChangedSettingsData->m_LastDaysCount                     = 3U;
  }
  else
  {
    // intentionally left blank
  }
}

void DefaultsSettingsScreen::HandleQuailLineEvent(const JoystickEvent &event)
{
  if (event.bIsLeftPressed)
  {
    SetNextScreen(SCREEN_TYPE_INCUBATOR_SETTINGS);
  }
  else if (event.bIsUpPressed)
  {
    m_SelectedLine = DEFAULTS_SETTINGS_SCREEN_LINE_DUCK;
    m_Lcd->MoveCursor(1U, 0U);
    m_Lcd->Print(" Tavuk    ");
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(" Kaz    ");
    m_Lcd->MoveCursor(3U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
    m_Lcd->Print(BSP_LCD_2004_CHAR_UPPER_O);
    m_Lcd->Print("rdek    ");
  }
  else if (event.bIsRightPressed || event.bIsButtonPressed)
  {
    SetNextScreen(SCREEN_TYPE_QUESTION_SAVE);
    m_Lcd->Clear();
    m_Lcd->MoveCursor(1U, 0U);
    m_Lcd->Print("B");
    m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
    m_Lcd->Print("ld");
    m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
    m_Lcd->Print("rc");
    m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
    m_Lcd->Print("n");
    m_ChangedSettingsData->m_TemperatureInMilliCelcius         = static_cast<uint32_t>(37500UL);
    m_ChangedSettingsData->m_LastDaysTemperatureInMilliCelcius = static_cast<uint32_t>(37100UL);
    m_ChangedSettingsData->m_HumidityInPercentage              = 67U;
    m_ChangedSettingsData->m_LastDaysHumidityInPercentage      = 75U;
    m_ChangedSettingsData->m_TotalIncubationDayCount           = 18U;
    m_ChangedSettingsData->m_LastDaysCount                     = 3U;
  }
  else
  {
    // intentionally left blank
  }
}

uint8_t DefaultsSettingsScreen::DetermineStartLine() const
{
  uint8_t result = 0U;
  if (static_cast<uint8_t>(m_SelectedLine) >= SCREEN_MAX_LINE_SIZE)
  {
    constexpr uint8_t SCREEN_LINE_OFFSET = SCREEN_MAX_LINE_SIZE - 1U;
    result = static_cast<uint8_t>(m_SelectedLine) - SCREEN_LINE_OFFSET;
  }
  return result;
}

void DefaultsSettingsScreen::PrintLine(const uint8_t lineNumber)
{
  switch (lineNumber)
  {
    case DEFAULTS_SETTINGS_SCREEN_LINE_CHICKEN:
    {
      m_Lcd->Print("Tavuk    ");
      break;
    }
    case DEFAULTS_SETTINGS_SCREEN_LINE_GOOSE:
    {
      m_Lcd->Print("Kaz    ");
      break;
    }
    case DEFAULTS_SETTINGS_SCREEN_LINE_DUCK:
    {
      m_Lcd->Print(BSP_LCD_2004_CHAR_UPPER_O);
      m_Lcd->Print("rdek    ");
      break;
    }
    case DEFAULTS_SETTINGS_SCREEN_LINE_QUAIL:
    {
      m_Lcd->Print("B");
      m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
      m_Lcd->Print("ld");
      m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
      m_Lcd->Print("rc");
      m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
      m_Lcd->Print("n");
      break;
    }

    default:
      break;
  }
}

DefaultsSettingsScreen::DefaultsSettingsScreen()
    : AScreen{SCREEN_TYPE_DEFAULTS_SETTINGS}, m_Lcd{nullptr},
      m_SelectedLine{DEFAULTS_SETTINGS_SCREEN_LINE_CHICKEN}, m_ChangedSettingsData{nullptr}
{
}

DefaultsSettingsScreen::~DefaultsSettingsScreen()
{
}

void DefaultsSettingsScreen::Initialize(Lcd2004 *tc2004Lcd, SettingsData *changedSettingsData)
{
  m_Lcd                 = tc2004Lcd;
  m_ChangedSettingsData = changedSettingsData;
  bsp_assert(nullptr != m_ChangedSettingsData);
}

void DefaultsSettingsScreen::OnInitial()
{
  Reset();
  m_Lcd->Clear();
  m_Lcd->MoveCursor(0U, 0U);
  m_Lcd->Print("[Varsay");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
  m_Lcd->Print("lanlar]");
  const uint8_t startLine = DetermineStartLine();
  for (uint8_t i = 0U; i < SCREEN_MAX_LINE_SIZE; i++)
  {
    const uint8_t currentLine    = startLine + i;
    constexpr uint8_t lineOffset = 1U;
    const uint8_t cursorLine     = i + lineOffset;
    m_Lcd->MoveCursor(cursorLine, 0U);
    if (currentLine == m_SelectedLine)
    {
      m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
    }
    else
    {
      m_Lcd->Print(" ");
    }
    PrintLine(currentLine);
  }
}

void DefaultsSettingsScreen::Run()
{
  // intentionally left blank
}

void DefaultsSettingsScreen::OnUserAction(const JoystickEvent &event)
{
  switch (m_SelectedLine)
  {
    case DEFAULTS_SETTINGS_SCREEN_LINE_CHICKEN:
    {
      HandleChickenLineEvent(event);
      break;
    }

    case DEFAULTS_SETTINGS_SCREEN_LINE_GOOSE:
    {
      HandleGooseLineEvent(event);
      break;
    }

    case DEFAULTS_SETTINGS_SCREEN_LINE_DUCK:
    {
      HandleDuckLineEvent(event);
      break;
    }

    case DEFAULTS_SETTINGS_SCREEN_LINE_QUAIL:
    {
      HandleQuailLineEvent(event);
      break;
    }

    default:
      break;
  }
  // intentionally left blank
}

} // namespace Incubator
