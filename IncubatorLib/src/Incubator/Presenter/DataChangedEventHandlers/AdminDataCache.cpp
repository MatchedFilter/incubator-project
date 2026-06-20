#include "Incubator/Presenter/DataChangedEventHandlers/AdminDataCache.h"

namespace Incubator
{
AdminDataCache::AdminDataCache() : m_Model{nullptr}, m_bUpdated{false}
{
}

AdminDataCache::~AdminDataCache()
{
}

void AdminDataCache::OnUpdate(const AdminData &data)
{
  if (false == m_bUpdated)
  {
    m_bUpdated = true;
  }
  m_AdminData.Copy(data);

  if (nullptr != m_Model)
  {
    m_Model->Update(data);
  }
  if (nullptr != m_View)
  {
    m_View->UpdateAdminData(data);
  }
}

bool AdminDataCache::GetPid(double &p, double &i, double &d) const
{
  bool bResult = false;
  if (m_bUpdated)
  {
    bResult = true;
    p       = static_cast<double>(m_AdminData.m_P) / 10.0;
    i       = static_cast<double>(m_AdminData.m_I) / 10.0;
    d       = static_cast<double>(m_AdminData.m_D) / 10.0;
  }
  return bResult;
}

bool AdminDataCache::GetHumidityHysterisisDiff(uint8_t &upperDiff, uint8_t &lowerDiff) const
{
  bool bResult = false;
  if (m_bUpdated)
  {
    bResult   = true;
    upperDiff = m_AdminData.m_UpperHumidityDifference;
    lowerDiff = m_AdminData.m_LowerHumidityDifference;
  }
  return bResult;
}

} // namespace Incubator
