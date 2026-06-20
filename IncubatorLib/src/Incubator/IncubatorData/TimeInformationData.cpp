#include "Incubator/IncubatorData/TimeInformationData.h"

namespace Incubator
{
void TimeInformationData::Reset()
{
  m_CurrentTimestampInSecond = static_cast<uint32_t>(0UL);
}

void TimeInformationData::Copy(const TimeInformationData &other)
{
  m_CurrentTimestampInSecond = other.m_CurrentTimestampInSecond;
}

} // namespace Incubator
