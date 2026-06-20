#include "Incubator/View/Screen/SettingsScreen.h"

#include "TimeUtils/TimerManager.h"

namespace Incubator
{

void SettingsScreen::HandleScreenLineIncubator(const JoystickEvent &event)
{
  if (event.bIsLeftPressed)
  {
    m_AdministratorEnterLevel = ADMINISTRATOR_ENTER_LEVEL_0;
    m_AdministratorClickTimerTask->Stop();
    SetNextScreen(SCREEN_TYPE_MENU);
  }
  else if (event.bIsDownPressed)
  {
    m_SelectedLine = SETTINGS_SCREEN_LINE_TIME;
    m_Lcd->MoveCursor(1U, 0U);
    m_Lcd->Print(" ");
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else if (event.bIsRightPressed || event.bIsButtonPressed)
  {
    SetNextScreen(SCREEN_TYPE_INCUBATOR_SETTINGS);
  }
  else
  {
    // intentionally left blank
  }
}

void SettingsScreen::HandleScreenLineTime(const JoystickEvent &event)
{
  if (event.bIsLeftPressed)
  {
    m_AdministratorEnterLevel = ADMINISTRATOR_ENTER_LEVEL_0;
    m_AdministratorClickTimerTask->Stop();
    SetNextScreen(SCREEN_TYPE_MENU);
  }
  else if (event.bIsUpPressed)
  {
    m_SelectedLine = SETTINGS_SCREEN_LINE_INCUBATOR;
    m_Lcd->MoveCursor(1U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(" ");
  }
  else if (event.bIsDownPressed)
  {
    m_SelectedLine = SETTINGS_SCREEN_LINE_ADMINISTRATOR;
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(" ");
    m_Lcd->MoveCursor(3U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else if (event.bIsRightPressed || event.bIsButtonPressed)
  {
    SetNextScreen(SCREEN_TYPE_TIME_SETTINGS);
  }
  else
  {
    // intentionally left blank
  }
}

void SettingsScreen::HandleScreenLineAdministrator(const JoystickEvent &event)
{
  if (event.bIsLeftPressed)
  {
    m_AdministratorEnterLevel = ADMINISTRATOR_ENTER_LEVEL_0;
    m_AdministratorClickTimerTask->Stop();
    SetNextScreen(SCREEN_TYPE_MENU);
  }
  else if (event.bIsUpPressed)
  {
    m_SelectedLine = SETTINGS_SCREEN_LINE_TIME;
    m_Lcd->MoveCursor(3U, 0U);
    m_Lcd->Print(" ");
    m_Lcd->MoveCursor(2U, 0U);
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else if (ADMINISTRATOR_ENTER_LEVEL_0 == m_AdministratorEnterLevel)
  {
    if (event.bIsRightPressed)
    {
      m_AdministratorEnterLevel = ADMINISTRATOR_ENTER_LEVEL_1;
      m_AdministratorClickTimerTask->Start();
    }
    else
    {
      m_AdministratorEnterLevel = ADMINISTRATOR_ENTER_LEVEL_0;
      m_AdministratorClickTimerTask->Stop();
    }
  }
  else if (ADMINISTRATOR_ENTER_LEVEL_1 == m_AdministratorEnterLevel)
  {
    if (event.bIsRightPressed)
    {
      m_AdministratorEnterLevel = ADMINISTRATOR_ENTER_LEVEL_2;
      m_AdministratorClickTimerTask->Start();
    }
    else
    {
      m_AdministratorEnterLevel = ADMINISTRATOR_ENTER_LEVEL_0;
      m_AdministratorClickTimerTask->Stop();
    }
  }

  else if (ADMINISTRATOR_ENTER_LEVEL_2 == m_AdministratorEnterLevel)
  {
    if (event.bIsRightPressed)
    {
      m_AdministratorEnterLevel = ADMINISTRATOR_ENTER_LEVEL_0;
      m_AdministratorClickTimerTask->Stop();
      SetNextScreen(SCREEN_TYPE_ADMINISTRATOR_SETTINGS);
    }
    else
    {
      m_AdministratorEnterLevel = ADMINISTRATOR_ENTER_LEVEL_0;
      m_AdministratorClickTimerTask->Stop();
    }
  }
  else
  {
    // intentionally left blank
  }
}

SettingsScreen::SettingsScreen()
    : AScreen{SCREEN_TYPE_SETTINGS}, m_Lcd{nullptr}, m_SelectedLine{SETTINGS_SCREEN_LINE_INCUBATOR},
      m_AdministratorEnterLevel{ADMINISTRATOR_ENTER_LEVEL_0}, m_AdministratorClickTimerTask{nullptr}
{
}

SettingsScreen::~SettingsScreen()
{
}

void SettingsScreen::Initialize(Lcd2004 *tc2004Lcd)
{
  m_Lcd                         = tc2004Lcd;
  m_AdministratorClickTimerTask = TimeUtils::TimerManager::CreateMillisecondTimer();
  m_AdministratorClickTimerTask->SetDuration(ADMINISTRATOR_CLICK_TIMEOUT_IN_MILLISECOND);
}

void SettingsScreen::OnInitial()
{
  Reset();
  m_AdministratorEnterLevel = ADMINISTRATOR_ENTER_LEVEL_0;
  m_Lcd->Clear();
  m_Lcd->MoveCursor(0U, 0U);
  m_Lcd->Print("[Ayarlar]");
  m_Lcd->MoveCursor(1U, 0U);
  if (SETTINGS_SCREEN_LINE_INCUBATOR == m_SelectedLine)
  {
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else
  {
    m_Lcd->Print(" ");
  }
  m_Lcd->Print("Kulu");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_C);
  m_Lcd->Print("ka");

  m_Lcd->MoveCursor(2U, 0U);
  if (SETTINGS_SCREEN_LINE_TIME == m_SelectedLine)
  {
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else
  {
    m_Lcd->Print(" ");
  }
  m_Lcd->Print("Zaman");

  m_Lcd->MoveCursor(3U, 0U);
  if (SETTINGS_SCREEN_LINE_ADMINISTRATOR == m_SelectedLine)
  {
    m_Lcd->Print(BSP_LCD_2004_CHAR_ARROW_SYMBOL);
  }
  else
  {
    m_Lcd->Print(" ");
  }
  m_Lcd->Print("Y");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_O);
  m_Lcd->Print("netici");
}

void SettingsScreen::Run()
{
  if (m_AdministratorClickTimerTask->IsFinished())
  {
    m_AdministratorEnterLevel = ADMINISTRATOR_ENTER_LEVEL_0;
    m_AdministratorClickTimerTask->Stop();
  }
  // intentionally left blank
}

void SettingsScreen::OnUserAction(const JoystickEvent &event)
{
  switch (m_SelectedLine)
  {
    case SETTINGS_SCREEN_LINE_INCUBATOR:
    {
      HandleScreenLineIncubator(event);
      break;
    }

    case SETTINGS_SCREEN_LINE_TIME:
    {
      HandleScreenLineTime(event);
      break;
    }

    case SETTINGS_SCREEN_LINE_ADMINISTRATOR:
    {
      HandleScreenLineAdministrator(event);
      break;
    }

    default:
      break;
  }
}

} // namespace Incubator
