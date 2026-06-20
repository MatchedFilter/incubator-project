#include "Incubator/View/Screen/DataSetScreen/HumidityLastDaysDataSetScreen.h"

namespace Incubator
{

HumidityLastDaysDataSetScreen::HumidityLastDaysDataSetScreen()
    : AHumidityDataSetScreen(SCREEN_TYPE_DATA_SET_HUMIDITY_LAST_DAYS)
{
}
HumidityLastDaysDataSetScreen::~HumidityLastDaysDataSetScreen()
{
}

uint8_t HumidityLastDaysDataSetScreen::GetCurrentHumidityInPercentage() const
{
  return m_CurrentIncubatorInformationData->m_SettingsData.m_LastDaysHumidityInPercentage;
}

uint8_t HumidityLastDaysDataSetScreen::GetChangedHumidityInPercentage() const
{
  return m_ChangedIncubatorInformationData->m_SettingsData.m_LastDaysHumidityInPercentage;
}

void HumidityLastDaysDataSetScreen::SetChangedHumidityInPercentage(
  const uint8_t humidityInPercentage)
{
  m_ChangedIncubatorInformationData->m_SettingsData.m_LastDaysHumidityInPercentage =
    humidityInPercentage;
}

} // namespace Incubator
