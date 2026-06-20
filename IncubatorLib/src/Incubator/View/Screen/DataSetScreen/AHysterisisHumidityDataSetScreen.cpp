#include "Incubator/View/Screen/DataSetScreen/AHysterisisHumidityDataSetScreen.h"

#include "Utils/StringUtils.h"

namespace Incubator
{

AHysterisisHumidityDataSetScreen::AHysterisisHumidityDataSetScreen(const EnumScreenType screenType)
    : ADataSetScreen(screenType)
{
}

AHysterisisHumidityDataSetScreen::~AHysterisisHumidityDataSetScreen()
{
}

void AHysterisisHumidityDataSetScreen::PrintCurrentData() const
{
  char humidityString[4] = {0U};
  static_cast<void>(Utils::StringUtils::ToCharArray(GetCurrentDifference(), humidityString));
  m_Lcd->Print(humidityString);
}

void AHysterisisHumidityDataSetScreen::PrintNewData() const
{
  char humidityString[4] = {0U};
  static_cast<void>(Utils::StringUtils::ToCharArray(GetChangedDifference(), humidityString));
  m_Lcd->Print(humidityString);
  m_Lcd->Print("    ");
}

void AHysterisisHumidityDataSetScreen::OnIncrementHighEvent()
{
  const uint8_t nextValue = GetChangedDifference() + HIGH_INCREMENT_CONSTANT;
  uint8_t resultValue     = MAX_ALLOWED_CONSTANT;
  if (nextValue < MAX_ALLOWED_CONSTANT)
  {
    resultValue = nextValue;
  }
  SetChangedDifference(resultValue);
}

void AHysterisisHumidityDataSetScreen::OnIncrementLowEvent()
{
  const uint8_t nextValue = GetChangedDifference() + LOW_INCREMENT_CONSTANT;
  uint8_t resultValue     = MAX_ALLOWED_CONSTANT;
  if (nextValue < MAX_ALLOWED_CONSTANT)
  {
    resultValue = nextValue;
  }
  SetChangedDifference(resultValue);
}

void AHysterisisHumidityDataSetScreen::OnDecrementHighEvent()
{
  const uint8_t changedValue = GetChangedDifference();
  uint8_t resultValue        = MIN_ALLOWED_CONSTANT;
  if (changedValue > HIGH_INCREMENT_CONSTANT)
  {
    const uint8_t nextValue = changedValue - HIGH_INCREMENT_CONSTANT;
    if (nextValue > MIN_ALLOWED_CONSTANT)
    {
      resultValue = nextValue;
    }
  }
  SetChangedDifference(resultValue);
}

void AHysterisisHumidityDataSetScreen::OnDecrementLowEvent()
{
  const uint8_t changedValue = GetChangedDifference();
  uint8_t resultValue        = MIN_ALLOWED_CONSTANT;
  if (changedValue > LOW_INCREMENT_CONSTANT)
  {
    const uint8_t nextValue = changedValue - LOW_INCREMENT_CONSTANT;
    if (nextValue > MIN_ALLOWED_CONSTANT)
    {
      resultValue = nextValue;
    }
  }
  SetChangedDifference(resultValue);
}

void AHysterisisHumidityDataSetScreen::NotifyChangedData()
{
  m_DataChangedEventHandlers->m_AdminDataChangedEventHandler->OnUpdate(
    m_ChangedIncubatorInformationData->m_AdminData);
}

EnumScreenType AHysterisisHumidityDataSetScreen::GetNextScreenForYesSelection() const
{
  return SCREEN_TYPE_HYSTERISIS_HUMIDITY;
}

EnumScreenType AHysterisisHumidityDataSetScreen::GetNextScreenForNoSelection() const
{
  return SCREEN_TYPE_HYSTERISIS_HUMIDITY;
}

} // namespace Incubator
