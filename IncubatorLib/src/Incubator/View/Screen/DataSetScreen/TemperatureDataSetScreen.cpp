#include "Incubator/View/Screen/DataSetScreen/TemperatureDataSetScreen.h"

namespace Incubator
{

TemperatureDataSetScreen::TemperatureDataSetScreen()
    : ATemperatureDataSetScreen(SCREEN_TYPE_DATA_SET_TEMPERATURE)
{
}

TemperatureDataSetScreen::~TemperatureDataSetScreen()
{
}

uint32_t TemperatureDataSetScreen::GetCurrentTemperatureInMilliCelcius() const
{
  return m_CurrentIncubatorInformationData->m_SettingsData.m_TemperatureInMilliCelcius;
}

uint32_t TemperatureDataSetScreen::GetChangedTemperatureInMilliCelcius() const
{
  return m_ChangedIncubatorInformationData->m_SettingsData.m_TemperatureInMilliCelcius;
}

void TemperatureDataSetScreen::SetChangedTemperatureInMilliCelcius(
  const uint32_t temperatureInMilliCelcius)
{
  m_ChangedIncubatorInformationData->m_SettingsData.m_TemperatureInMilliCelcius =
    temperatureInMilliCelcius;
}

} // namespace Incubator
