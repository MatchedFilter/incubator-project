#include "Incubator/View/Screen/DataSetScreen/ATemperatureDataSetScreen.h"

#include "Utils/StringUtils.h"

namespace Incubator
{

ATemperatureDataSetScreen::ATemperatureDataSetScreen(const EnumScreenType screenType)
    : ADataSetScreen(screenType)
{
}

ATemperatureDataSetScreen::~ATemperatureDataSetScreen()
{
}

static auto GetTemperatureString(const int32_t temperatureInMillicelcius, char (&chrArr)[10]);
static auto GetTemperatureString(const int32_t temperatureInMillicelcius, char (&chrArr)[10])
{
  uint32_t index = 0U;

  index += Utils::StringUtils::ToCharArray(temperatureInMillicelcius / 1000, chrArr, index);
  chrArr[index++] = '.';
  index += Utils::StringUtils::ToCharArray((temperatureInMillicelcius % 1000 / 100), chrArr, index);
}

void ATemperatureDataSetScreen::PrintCurrentData() const
{
  char temperatureString[10] = {0};
  GetTemperatureString(GetCurrentTemperatureInMilliCelcius(), temperatureString);
  m_Lcd->Print(temperatureString);
  m_Lcd->Print(BSP_LCD_2004_CHAR_DEGREE_SYMBOL);
  m_Lcd->Print("C  ");
}

void ATemperatureDataSetScreen::PrintNewData() const
{
  char temperatureString[10] = {0};
  GetTemperatureString(GetChangedTemperatureInMilliCelcius(), temperatureString);
  m_Lcd->Print(temperatureString);
  m_Lcd->Print(BSP_LCD_2004_CHAR_DEGREE_SYMBOL);
  m_Lcd->Print("C  ");
}

void ATemperatureDataSetScreen::OnIncrementHighEvent()
{
  const uint32_t nextTemperatureInMilliCelcius =
    GetChangedTemperatureInMilliCelcius() + HIGH_INCREMENT_IN_MILLICELCIUS;
  uint32_t resultTemperatureInMilliCelcius = MAX_ALLOWED_TEMPERATURE_IN_MILLICELCIUS;
  if (nextTemperatureInMilliCelcius < MAX_ALLOWED_TEMPERATURE_IN_MILLICELCIUS)
  {
    resultTemperatureInMilliCelcius = nextTemperatureInMilliCelcius;
  }
  SetChangedTemperatureInMilliCelcius(resultTemperatureInMilliCelcius);
}

void ATemperatureDataSetScreen::OnIncrementLowEvent()
{
  const uint32_t nextTemperatureInMilliCelcius =
    GetChangedTemperatureInMilliCelcius() + LOW_INCREMENT_IN_MILLICELCIUS;
  uint32_t resultTemperatureInMilliCelcius = MAX_ALLOWED_TEMPERATURE_IN_MILLICELCIUS;
  if (nextTemperatureInMilliCelcius < MAX_ALLOWED_TEMPERATURE_IN_MILLICELCIUS)
  {
    resultTemperatureInMilliCelcius = nextTemperatureInMilliCelcius;
  }
  SetChangedTemperatureInMilliCelcius(resultTemperatureInMilliCelcius);
}

void ATemperatureDataSetScreen::OnDecrementHighEvent()
{
  const uint32_t changedTemperatureInMilliCelcius = GetChangedTemperatureInMilliCelcius();
  uint32_t resultTemperatureInMilliCelcius        = MIN_ALLOWED_TEMPERATURE_IN_MILLICELCIUS;
  if (changedTemperatureInMilliCelcius > HIGH_INCREMENT_IN_MILLICELCIUS)
  {
    const uint32_t nextTemperatureInMilliCelcius =
      changedTemperatureInMilliCelcius - HIGH_INCREMENT_IN_MILLICELCIUS;
    if (nextTemperatureInMilliCelcius > MIN_ALLOWED_TEMPERATURE_IN_MILLICELCIUS)
    {
      resultTemperatureInMilliCelcius = nextTemperatureInMilliCelcius;
    }
  }
  SetChangedTemperatureInMilliCelcius(resultTemperatureInMilliCelcius);
}

void ATemperatureDataSetScreen::OnDecrementLowEvent()
{
  const uint32_t changedTemperatureInMilliCelcius = GetChangedTemperatureInMilliCelcius();
  uint32_t resultTemperatureInMilliCelcius        = MIN_ALLOWED_TEMPERATURE_IN_MILLICELCIUS;
  if (changedTemperatureInMilliCelcius > LOW_INCREMENT_IN_MILLICELCIUS)
  {
    const uint32_t nextTemperatureInMilliCelcius =
      changedTemperatureInMilliCelcius - LOW_INCREMENT_IN_MILLICELCIUS;
    if (nextTemperatureInMilliCelcius > MIN_ALLOWED_TEMPERATURE_IN_MILLICELCIUS)
    {
      resultTemperatureInMilliCelcius = nextTemperatureInMilliCelcius;
    }
  }
  SetChangedTemperatureInMilliCelcius(resultTemperatureInMilliCelcius);
}

void ATemperatureDataSetScreen::NotifyChangedData()
{
  m_DataChangedEventHandlers->m_SettingsDataChangedEventHandler->OnUpdate(
    m_ChangedIncubatorInformationData->m_SettingsData);
}

EnumScreenType ATemperatureDataSetScreen::GetNextScreenForNoSelection() const
{
  return SCREEN_TYPE_TEMPERATURE_SETTINGS;
}

} // namespace Incubator
