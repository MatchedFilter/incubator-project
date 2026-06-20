#ifndef INCUBATOR_ISETTINGSDATACHANGEDEVENTHANDLER_H
#define INCUBATOR_ISETTINGSDATACHANGEDEVENTHANDLER_H
#include "Incubator/IncubatorData/SettingsData.h"
namespace Incubator
{
class ISettingsDataChangedEventHandler
{
public:
  inline virtual ~ISettingsDataChangedEventHandler()
  {
  }
  virtual void OnUpdate(const SettingsData &data) = 0;
};
} // namespace Incubator

#endif // INCUBATOR_ISETTINGSDATACHANGEDEVENTHANDLER_H
