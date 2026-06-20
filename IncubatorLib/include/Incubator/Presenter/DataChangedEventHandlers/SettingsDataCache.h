#ifndef INCUBATOR_SETTINGSDATACACHE_H
#define INCUBATOR_SETTINGSDATACACHE_H
#include "Incubator/Model/IModel.h"
#include "Incubator/View/DataChangedEventHandler/ISettingsDataChangedEventHandler.h"
#include "Incubator/View/IView.h"

namespace Incubator
{
class SettingsDataCache : public ISettingsDataChangedEventHandler
{
public:
  SettingsDataCache();
  virtual ~SettingsDataCache();
  inline void Initialize(IModel *model, IView *view)
  {
    m_Model = model;
    m_View  = view;
  }
  virtual void OnUpdate(const SettingsData &data) override;
  bool GetSettingsData(SettingsData &data) const;

private:
  IModel *m_Model;
  IView *m_View;
  bool m_bUpdated;
  SettingsData m_SettingsData;
};
} // namespace Incubator

#endif // INCUBATOR_SETTINGSDATACACHE_H
