#include "Incubator/View/Screen/MainScreen.h"

#include "TimeUtils/TimeSettings.h"
#include "TimeUtils/TimerManager.h"
#include "Utils/StringUtils.h"

#include <cstring>

namespace Incubator
{

void MainScreen::DisplayTemperature() const
{
  char temperatureString[11] = {0};
  uint8_t index              = 0U;
  index += Utils::StringUtils::ToCharArray(static_cast<int32_t>(m_TemperatureInCelcius),
                                           temperatureString, index);
  temperatureString[index++] = '.';
  index += Utils::StringUtils::ToCharArray(static_cast<int32_t>(m_TemperatureInCelcius * 10.0) % 10,
                                           temperatureString, index);
  m_Lcd->Print(temperatureString);
}

void MainScreen::DisplayTargetTemperature() const
{
  const uint8_t currentDay = static_cast<uint8_t>(
    m_TimeInformationData.m_CurrentTimestampInSecond /
    (static_cast<uint32_t>(60UL) * static_cast<uint32_t>(60UL) * static_cast<uint32_t>(24UL)));
  const uint32_t temperatureInMilliCelcius =
    (currentDay >= (m_SettingsData.m_TotalIncubationDayCount - m_SettingsData.m_LastDaysCount))
      ? m_SettingsData.m_LastDaysTemperatureInMilliCelcius
      : m_SettingsData.m_TemperatureInMilliCelcius;

  char temperatureString[11] = {0};
  uint8_t index              = 0U;
  index +=
    Utils::StringUtils::ToCharArray(temperatureInMilliCelcius / 1000U, temperatureString, index);
  temperatureString[index++] = '.';
  index += Utils::StringUtils::ToCharArray((temperatureInMilliCelcius % 1000U) / 100U,
                                           temperatureString, index);
  m_Lcd->Print(temperatureString);
}

void MainScreen::DisplayTargetHumidity() const
{
  const uint8_t currentDay = static_cast<uint8_t>(
    m_TimeInformationData.m_CurrentTimestampInSecond /
    (static_cast<uint32_t>(60UL) * static_cast<uint32_t>(60UL) * static_cast<uint32_t>(24UL)));
  const uint8_t humidityInPercent =
    (currentDay >= (m_SettingsData.m_TotalIncubationDayCount - m_SettingsData.m_LastDaysCount))
      ? m_SettingsData.m_LastDaysHumidityInPercentage
      : m_SettingsData.m_HumidityInPercentage;

  char humidityString[4] = {0};
  static_cast<void>(Utils::StringUtils::ToCharArray(humidityInPercent, humidityString));
  m_Lcd->Print(humidityString);
}

void MainScreen::DisplayTemperatureInformation()
{
  if (m_bIsTemperatureSet)
  {
    m_Lcd->MoveCursor(0U, 4U);
    if (false == (m_TemperatureInCelcius < 0.0))
    {
      m_Lcd->Print(" ");
    }
    else
    {
      m_Lcd->Print("    ");
      m_Lcd->MoveCursor(0U, 4U);
    }
    DisplayTemperature();
  }
  if (m_bIsIncubatorDataProvided)
  {
    m_Lcd->MoveCursor(0U, 12U);
    DisplayTargetTemperature();
    m_Lcd->Print(BSP_LCD_2004_CHAR_DEGREE_SYMBOL);
    m_Lcd->Print("C  ");
  }
}

void MainScreen::StartToDisplayTemperatureInformation()
{
  m_Lcd->MoveCursor(0U, 0U);
  m_Lcd->Print("Sck: ---- / ----    ");
}

void MainScreen::DisplayTemperatureFailure()
{
  m_Lcd->MoveCursor(0U, 0U);
  m_Lcd->Print("Sck Hatas");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
  m_Lcd->Print("          ");
  m_Lcd->MoveCursor(3U, 0U);
}

void MainScreen::DisplayHumidityInformation()
{
  if (m_bIsHumiditySet)
  {
    m_Lcd->MoveCursor(1U, 5U);
    char humidityString[4] = {0};
    uint8_t index          = 0U;
    if (m_HumidityInPercent < 10U)
    {
      humidityString[index++] = ' ';
    }
    index += Utils::StringUtils::ToCharArray(m_HumidityInPercent, humidityString, index);
    if (m_HumidityInPercent < 100U)
    {
      humidityString[index++] = ' ';
    }
    m_Lcd->Print(humidityString);
  }
  if (m_bIsIncubatorDataProvided)
  {
    m_Lcd->MoveCursor(1U, 10U);
    DisplayTargetHumidity();
    m_Lcd->Print("%  ");
  }
}

void MainScreen::StartToDisplayHumidityInformation()
{
  m_Lcd->MoveCursor(1U, 0U);
  m_Lcd->Print("Nem: -- / --        ");
}

void MainScreen::DisplayHumidityFailure()
{
  m_Lcd->MoveCursor(1U, 0U);
  m_Lcd->Print("Nem Hatas");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
  m_Lcd->Print("          ");
}

void MainScreen::DisplayTimeInformation()
{
  if (m_bTimeInformationProvided)
  {
    DisplayDay();
    DisplayHour();
    DisplayMinute();
    DisplaySecond();
  }
}

void MainScreen::DisplayDay()
{
  m_Lcd->MoveCursor(2U, 5U);
  char dayString[4] = {0};
  uint8_t index     = 0U;

  const uint8_t currentDay = static_cast<uint8_t>(
    ((TimeUtils::TimeSettings::GetIncubatorTimeInSeconds() / static_cast<uint32_t>(60UL)) /
     static_cast<uint32_t>(60UL)) /
    static_cast<uint32_t>(24UL));
  if (currentDay < 10U)
  {
    dayString[index++] = ' ';
  }
  static_cast<void>(Utils::StringUtils::ToCharArray(currentDay, dayString, index));
  m_Lcd->Print(dayString);

  static_cast<void>(std::memset(dayString, 0, sizeof(dayString)));
  index = 0U;

  m_Lcd->MoveCursor(2U, 10U);
  if (m_SettingsData.m_TotalIncubationDayCount < 10U)
  {
    dayString[index++] = ' ';
  }
  static_cast<void>(
    Utils::StringUtils::ToCharArray(m_SettingsData.m_TotalIncubationDayCount, dayString, index));
  m_Lcd->Print(dayString);
}

void MainScreen::DisplayHour()
{
  m_Lcd->MoveCursor(3U, 5U);
  const uint8_t currentHour = static_cast<uint8_t>(
    ((TimeUtils::TimeSettings::GetIncubatorTimeInSeconds() / static_cast<uint32_t>(60UL)) /
     static_cast<uint32_t>(60UL)) %
    static_cast<uint32_t>(24UL));

  char hourString[4] = {0};
  uint8_t index      = 0U;
  if (currentHour < 10U)
  {
    hourString[index++] = ' ';
  }
  static_cast<void>(Utils::StringUtils::ToCharArray(currentHour, hourString, index));
  m_Lcd->Print(hourString);
}

void MainScreen::DisplayMinute()
{
  m_Lcd->MoveCursor(3U, 11U);
  const uint8_t currentMinute = static_cast<uint8_t>(
    (TimeUtils::TimeSettings::GetIncubatorTimeInSeconds() / static_cast<uint32_t>(60UL)) %
    static_cast<uint32_t>(60UL));

  char minuteString[4] = {0};
  uint8_t index        = 0U;
  if (currentMinute < 10U)
  {
    minuteString[index++] = ' ';
  }
  static_cast<void>(Utils::StringUtils::ToCharArray(currentMinute, minuteString, index));
  m_Lcd->Print(minuteString);
}

void MainScreen::DisplaySecond()
{
  m_Lcd->MoveCursor(3U, 16U);
  const uint8_t currentSecond = static_cast<uint8_t>(
    TimeUtils::TimeSettings::GetIncubatorTimeInSeconds() % static_cast<uint32_t>(60UL));

  char secondString[4] = {0};
  uint8_t index        = 0U;
  if (currentSecond < 10U)
  {
    secondString[index++] = ' ';
  }
  static_cast<void>(Utils::StringUtils::ToCharArray(currentSecond, secondString, index));
  m_Lcd->Print(secondString);
}

MainScreen::MainScreen()
    : AScreen{SCREEN_TYPE_MAIN}, m_Lcd{nullptr}, m_bIsTemperatureSet{false},
      m_TemperatureInCelcius{0.0}, m_bIsHumiditySet{false}, m_HumidityInPercent{0U},
      m_bIsIncubatorDataProvided{false}, m_bIsSettingsProvided{false},
      m_bTimeInformationProvided{false}, m_ScreenInformationUpdateTimerTask{nullptr},
      m_bModelValid{true}, m_TemperatureUpdateStatus{UPDATE_STATUS_VALID},
      m_HumidityUpdateStatus{UPDATE_STATUS_VALID}
{
}

MainScreen::~MainScreen()
{
}

void MainScreen::Initialize(Lcd2004 *tc2004Lcd)
{
  m_Lcd                              = tc2004Lcd;
  m_ScreenInformationUpdateTimerTask = TimeUtils::TimerManager::CreateMillisecondTimer();
  OnInitial();
  m_ScreenInformationUpdateTimerTask->SetDuration(static_cast<uint32_t>(500UL));
  m_ScreenInformationUpdateTimerTask->Start();
}

void MainScreen::OnInitial()
{
  Reset();
  m_Lcd->Clear();
  m_Lcd->MoveCursor(0U, 0U);
  m_Lcd->Print("Sck: ---- / ----");
  m_Lcd->MoveCursor(1U, 0U);
  m_Lcd->Print("Nem: -- / --");
  m_Lcd->MoveCursor(2U, 0U);
  m_Lcd->Print("G");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_U);
  m_Lcd->Print("n: -- / --");
  m_Lcd->MoveCursor(3U, 0U);
  m_Lcd->Print("Saat:-- Dk:-- S:--");
}

void MainScreen::UpdateSettingsData(const SettingsData &data)
{
  m_SettingsData.Copy(data);
  m_bIsSettingsProvided = true;
  if (m_bTimeInformationProvided)
  {
    m_bIsIncubatorDataProvided = true;
  }
}

void MainScreen::UpdateTimeInformationData(const TimeInformationData &data)
{
  m_TimeInformationData.Copy(data);
  m_bTimeInformationProvided = true;
  if (m_bIsSettingsProvided)
  {
    m_bIsIncubatorDataProvided = true;
  }
}

void MainScreen::UpdateTemperature(const double &temperatureInCelcius)
{
  if (UPDATE_STATUS_INVALID == m_TemperatureUpdateStatus)
  {
    m_TemperatureUpdateStatus = UPDATE_STATUS_VALID;
  }
  m_bIsTemperatureSet    = true;
  m_TemperatureInCelcius = temperatureInCelcius;
}

void MainScreen::UpdateHumidity(const uint8_t &humidityInPercent)
{
  if (UPDATE_STATUS_INVALID == m_HumidityUpdateStatus)
  {
    m_HumidityUpdateStatus = UPDATE_STATUS_VALID;
  }
  m_bIsHumiditySet    = true;
  m_HumidityInPercent = humidityInPercent;
}

void MainScreen::OnTemperatureFailure()
{
  if (m_bModelValid)
  {
    if (UPDATE_STATUS_INVALID != m_TemperatureUpdateStatus)
    {
      m_TemperatureUpdateStatus = UPDATE_STATUS_INVALID;
    }
  }
}

void MainScreen::OnHumidityFailure()
{
  if (m_bModelValid)
  {
    if (UPDATE_STATUS_INVALID != m_HumidityUpdateStatus)
    {
      m_HumidityUpdateStatus = UPDATE_STATUS_INVALID;
    }
  }
}

void MainScreen::OnModelFailure()
{
  if (m_bModelValid)
  {
    m_bModelValid = false;
    m_Lcd->Clear();
    m_Lcd->Print("HATA: NVM1");
  }
}

void MainScreen::Run()
{
  if (m_bModelValid)
  {
    if (m_ScreenInformationUpdateTimerTask->IsFinished())
    {
      m_ScreenInformationUpdateTimerTask->Start();
      if (UPDATE_STATUS_SCREEN_UPDATED == m_HumidityUpdateStatus)
      {
        DisplayHumidityInformation();
      }
      else if (UPDATE_STATUS_VALID == m_HumidityUpdateStatus)
      {
        m_HumidityUpdateStatus = UPDATE_STATUS_SCREEN_UPDATED;
        StartToDisplayHumidityInformation();
      }
      else
      {
        DisplayHumidityFailure();
      }

      if (UPDATE_STATUS_SCREEN_UPDATED == m_TemperatureUpdateStatus)
      {
        DisplayTemperatureInformation();
      }
      else if (UPDATE_STATUS_VALID == m_TemperatureUpdateStatus)
      {
        m_TemperatureUpdateStatus = UPDATE_STATUS_SCREEN_UPDATED;
        StartToDisplayTemperatureInformation();
      }
      else
      {
        DisplayTemperatureFailure();
      }

      DisplayTimeInformation();
    }
  }
}

void MainScreen::OnUserAction(const JoystickEvent &event)
{
  if (event.bIsButtonPressed)
  {
    SetNextScreen(SCREEN_TYPE_MENU);
  }
}

} // namespace Incubator
