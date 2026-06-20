#include "Incubator/View/Screen/DataSetScreen/HumidityDataSetScreen.h"

namespace Incubator
{

HumidityDataSetScreen::HumidityDataSetScreen()
    : AHumidityDataSetScreen(SCREEN_TYPE_DATA_SET_HUMIDITY)
{
}

HumidityDataSetScreen::~HumidityDataSetScreen()
{
}

uint8_t HumidityDataSetScreen::GetCurrentHumidityInPercentage() const
{
  return m_CurrentIncubatorInformationData->m_SettingsData.m_HumidityInPercentage;
}

uint8_t HumidityDataSetScreen::GetChangedHumidityInPercentage() const
{
  return m_ChangedIncubatorInformationData->m_SettingsData.m_HumidityInPercentage;
}

void HumidityDataSetScreen::SetChangedHumidityInPercentage(const uint8_t humidityInPercentage)
{
  m_ChangedIncubatorInformationData->m_SettingsData.m_HumidityInPercentage = humidityInPercentage;
}

} // namespace Incubator
