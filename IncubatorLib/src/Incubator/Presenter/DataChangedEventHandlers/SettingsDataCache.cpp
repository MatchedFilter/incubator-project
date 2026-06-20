#include "Incubator/Presenter/DataChangedEventHandlers/SettingsDataCache.h"

namespace Incubator
{
SettingsDataCache::SettingsDataCache() : m_Model{nullptr}, m_View{nullptr}, m_bUpdated{false}
{
}

SettingsDataCache::~SettingsDataCache()
{
}

void SettingsDataCache::OnUpdate(const SettingsData &data)
{
  if (false == m_bUpdated)
  {
    m_bUpdated = true;
  }
  m_SettingsData.Copy(data);
  if (nullptr != m_Model)
  {
    m_Model->Update(data);
  }
  if (nullptr != m_View)
  {
    m_View->UpdateSettingsData(data);
  }
}

bool SettingsDataCache::GetSettingsData(SettingsData &data) const
{
  bool bResult = false;
  if (m_bUpdated)
  {
    bResult = true;
    data.Copy(m_SettingsData);
  }
  return bResult;
}

} // namespace Incubator
