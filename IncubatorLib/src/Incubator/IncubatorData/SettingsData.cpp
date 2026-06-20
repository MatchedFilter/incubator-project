#include "Incubator/IncubatorData/SettingsData.h"

namespace Incubator
{
void SettingsData::Reset()
{
  m_TemperatureInMilliCelcius         = static_cast<uint32_t>(37500UL);
  m_LastDaysTemperatureInMilliCelcius = static_cast<uint32_t>(36900UL);
  m_HumidityInPercentage              = 59U;
  m_LastDaysHumidityInPercentage      = 67U;
  m_TotalIncubationDayCount           = 21U;
  m_LastDaysCount                     = 3U;
}

void SettingsData::Copy(const SettingsData &other)
{
  m_TemperatureInMilliCelcius         = other.m_TemperatureInMilliCelcius;
  m_LastDaysTemperatureInMilliCelcius = other.m_LastDaysTemperatureInMilliCelcius;
  m_HumidityInPercentage              = other.m_HumidityInPercentage;
  m_LastDaysHumidityInPercentage      = other.m_LastDaysHumidityInPercentage;
  m_TotalIncubationDayCount           = other.m_TotalIncubationDayCount;
  m_LastDaysCount                     = other.m_LastDaysCount;
}

} // namespace Incubator
