#include "Incubator/IncubatorData/IncubatorInformationData.h"

namespace Incubator
{
void IncubatorInformationData::Reset()
{
  m_AdminData.Reset();
  m_SettingsData.Reset();
  m_TimeInformationData.Reset();
}

void IncubatorInformationData::Copy(const IncubatorInformationData &other)
{
  m_AdminData.Copy(other.m_AdminData);
  m_SettingsData.Copy(other.m_SettingsData);
  m_TimeInformationData.Copy(other.m_TimeInformationData);
}

} // namespace Incubator
