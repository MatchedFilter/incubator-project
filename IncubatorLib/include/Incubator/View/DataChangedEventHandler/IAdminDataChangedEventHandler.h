#ifndef INCUBATOR_IADMINDATACHANGEDEVENTHANDLER_H
#define INCUBATOR_IADMINDATACHANGEDEVENTHANDLER_H
#include "Incubator/IncubatorData/AdminData.h"
namespace Incubator
{
class IAdminDataChangedEventHandler
{
public:
  inline virtual ~IAdminDataChangedEventHandler()
  {
  }
  virtual void OnUpdate(const AdminData &data) = 0;
};
} // namespace Incubator

#endif // INCUBATOR_IADMINDATACHANGEDEVENTHANDLER_H
