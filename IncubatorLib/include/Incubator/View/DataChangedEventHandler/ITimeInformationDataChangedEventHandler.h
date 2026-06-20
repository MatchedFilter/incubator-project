#ifndef INCUBATOR_ITIMEINFORMATIONDATACHANGEDEVENTHANDLER_H
#define INCUBATOR_ITIMEINFORMATIONDATACHANGEDEVENTHANDLER_H
#include "Incubator/IncubatorData/TimeInformationData.h"
namespace Incubator
{
class ITimeInformationDataChangedEventHandler
{
public:
  inline virtual ~ITimeInformationDataChangedEventHandler()
  {
  }
  virtual void OnUpdate(const TimeInformationData &data) = 0;
};
} // namespace Incubator

#endif // INCUBATOR_ITIMEINFORMATIONDATACHANGEDEVENTHANDLER_H
