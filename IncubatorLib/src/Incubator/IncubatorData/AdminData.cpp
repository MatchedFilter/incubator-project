#include "Incubator/IncubatorData/AdminData.h"

namespace Incubator
{
void AdminData::Reset()
{
  m_P                       = static_cast<int32_t>(600L);
  m_I                       = static_cast<int32_t>(0L);
  m_D                       = static_cast<int32_t>(0L);
  m_UpperHumidityDifference = 3U;
  m_LowerHumidityDifference = 3U;
}

void AdminData::Copy(const AdminData &other)
{
  m_P                       = other.m_P;
  m_I                       = other.m_I;
  m_D                       = other.m_D;
  m_UpperHumidityDifference = other.m_UpperHumidityDifference;
  m_LowerHumidityDifference = other.m_LowerHumidityDifference;
}

} // namespace Incubator
