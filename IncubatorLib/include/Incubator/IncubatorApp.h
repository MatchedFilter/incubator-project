#ifndef INCUBATOR_INCUBATORAPP_H
#define INCUBATOR_INCUBATORAPP_H
#include "TimeUtils/MillisecondTimer.h"
#include "UsbCommandHandler.h"
#include "UsbTransmissionHandler.h"
namespace Incubator
{
class IncubatorApp
{
public:
  IncubatorApp()  = default;
  ~IncubatorApp() = default;
  auto Initialize(void) -> void;
  auto Run(void) -> void;

private:
  TimeUtils::MillisecondTimer *m_Timer = nullptr;
  UsbCommandHandler m_UsbCommandHandler;
  UsbTransmissionHandler m_UsbTransmissionHandler;
};
} // namespace Incubator
#endif // INCUBATOR_INCUBATORAPP_H
