#ifndef INCUBATOR_DATACHANGEDEVENTHANDLERS_H
#define INCUBATOR_DATACHANGEDEVENTHANDLERS_H
#include "IAdminDataChangedEventHandler.h"
#include "ISettingsDataChangedEventHandler.h"
#include "ITimeInformationDataChangedEventHandler.h"

namespace Incubator
{
struct DataChangedEventHandlers
{
  IAdminDataChangedEventHandler *m_AdminDataChangedEventHandler;
  ISettingsDataChangedEventHandler *m_SettingsDataChangedEventHandler;
  ITimeInformationDataChangedEventHandler *m_TimeInformationDataChangedEventHandler;
  inline void Reset()
  {
    m_AdminDataChangedEventHandler           = nullptr;
    m_SettingsDataChangedEventHandler        = nullptr;
    m_TimeInformationDataChangedEventHandler = nullptr;
  }

  inline void Copy(const DataChangedEventHandlers &other)
  {
    m_AdminDataChangedEventHandler           = other.m_AdminDataChangedEventHandler;
    m_SettingsDataChangedEventHandler        = other.m_SettingsDataChangedEventHandler;
    m_TimeInformationDataChangedEventHandler = other.m_TimeInformationDataChangedEventHandler;
  }
};

} // namespace Incubator

#endif // INCUBATOR_DATACHANGEDEVENTHANDLERS_H
