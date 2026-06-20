#include "Incubator/View/Screen/DataSetScreen/TemperatureLastDaysDataSetScreen.h"

namespace Incubator
{

TemperatureLastDaysDataSetScreen::TemperatureLastDaysDataSetScreen()
    : ATemperatureDataSetScreen(SCREEN_TYPE_DATA_SET_TEMPERATURE_LAST_DAYS)
{
}

TemperatureLastDaysDataSetScreen::~TemperatureLastDaysDataSetScreen()
{
}

uint32_t TemperatureLastDaysDataSetScreen::GetCurrentTemperatureInMilliCelcius() const
{
  return m_CurrentIncubatorInformationData->m_SettingsData.m_LastDaysTemperatureInMilliCelcius;
}

uint32_t TemperatureLastDaysDataSetScreen::GetChangedTemperatureInMilliCelcius() const
{
  return m_ChangedIncubatorInformationData->m_SettingsData.m_LastDaysTemperatureInMilliCelcius;
}

void TemperatureLastDaysDataSetScreen::SetChangedTemperatureInMilliCelcius(
  const uint32_t temperatureInMilliCelcius)
{
  m_ChangedIncubatorInformationData->m_SettingsData.m_LastDaysTemperatureInMilliCelcius =
    temperatureInMilliCelcius;
}

} // namespace Incubator
