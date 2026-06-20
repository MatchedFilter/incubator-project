#include "Incubator/View/Screen/DataSetScreen/AHumidityDataSetScreen.h"

#include "Utils/StringUtils.h"

namespace Incubator
{

AHumidityDataSetScreen::AHumidityDataSetScreen(const EnumScreenType screenType)
    : ADataSetScreen(screenType)
{
}

AHumidityDataSetScreen::~AHumidityDataSetScreen()
{
}

void AHumidityDataSetScreen::PrintCurrentData() const
{
  char humidityString[4] = {0U};
  static_cast<void>(
    Utils::StringUtils::ToCharArray(GetCurrentHumidityInPercentage(), humidityString));

  m_Lcd->Print(humidityString);
  m_Lcd->Print("%  ");
}

void AHumidityDataSetScreen::PrintNewData() const
{
  char humidityString[4] = {0U};
  static_cast<void>(
    Utils::StringUtils::ToCharArray(GetChangedHumidityInPercentage(), humidityString));
  m_Lcd->Print(humidityString);
  m_Lcd->Print("%  ");
}

void AHumidityDataSetScreen::OnIncrementHighEvent()
{
  const uint8_t nextHumidityInPercentage =
    GetChangedHumidityInPercentage() + HIGH_INCREMENT_IN_PERCENTAGE;
  uint8_t resultHumidityInPercentage = MAX_ALLOWED_HUMIDITY_IN_PERCENTAGE;
  if (nextHumidityInPercentage < MAX_ALLOWED_HUMIDITY_IN_PERCENTAGE)
  {
    resultHumidityInPercentage = nextHumidityInPercentage;
  }
  SetChangedHumidityInPercentage(resultHumidityInPercentage);
}

void AHumidityDataSetScreen::OnIncrementLowEvent()
{
  const uint8_t nextHumidityInPercentage =
    GetChangedHumidityInPercentage() + LOW_INCREMENT_IN_PERCENTAGE;
  uint8_t resultHumidityInPercentage = MAX_ALLOWED_HUMIDITY_IN_PERCENTAGE;
  if (nextHumidityInPercentage < MAX_ALLOWED_HUMIDITY_IN_PERCENTAGE)
  {
    resultHumidityInPercentage = nextHumidityInPercentage;
  }
  SetChangedHumidityInPercentage(resultHumidityInPercentage);
}

void AHumidityDataSetScreen::OnDecrementHighEvent()
{
  const uint8_t changedHumidityInPercentage = GetChangedHumidityInPercentage();
  uint8_t resultHumidityInPercentage        = MIN_ALLOWED_HUMIDITY_IN_PERCENTAGE;
  if (changedHumidityInPercentage > HIGH_INCREMENT_IN_PERCENTAGE)
  {
    const uint8_t nextHumidityInPercentage =
      changedHumidityInPercentage - HIGH_INCREMENT_IN_PERCENTAGE;
    if (nextHumidityInPercentage > MIN_ALLOWED_HUMIDITY_IN_PERCENTAGE)
    {
      resultHumidityInPercentage = nextHumidityInPercentage;
    }
  }
  SetChangedHumidityInPercentage(resultHumidityInPercentage);
}

void AHumidityDataSetScreen::OnDecrementLowEvent()
{
  const uint8_t changedHumidityInPercentage = GetChangedHumidityInPercentage();
  uint8_t resultHumidityInPercentage        = MIN_ALLOWED_HUMIDITY_IN_PERCENTAGE;
  if (changedHumidityInPercentage > LOW_INCREMENT_IN_PERCENTAGE)
  {
    const uint8_t nextHumidityInPercentage =
      changedHumidityInPercentage - LOW_INCREMENT_IN_PERCENTAGE;
    if (nextHumidityInPercentage > MIN_ALLOWED_HUMIDITY_IN_PERCENTAGE)
    {
      resultHumidityInPercentage = nextHumidityInPercentage;
    }
  }
  SetChangedHumidityInPercentage(resultHumidityInPercentage);
}

void AHumidityDataSetScreen::NotifyChangedData()
{
  m_DataChangedEventHandlers->m_SettingsDataChangedEventHandler->OnUpdate(
    m_ChangedIncubatorInformationData->m_SettingsData);
}

EnumScreenType AHumidityDataSetScreen::GetNextScreenForNoSelection() const
{
  return SCREEN_TYPE_HUMIDITY_SETTINGS;
}

} // namespace Incubator
