#ifndef INCUBATOR_USBTRANSMISSIONHANDLER_H
#define INCUBATOR_USBTRANSMISSIONHANDLER_H
#include "TimeUtils/MillisecondTimer.h"
namespace Incubator
{
class UsbTransmissionHandler
{
public:
  UsbTransmissionHandler()  = default;
  ~UsbTransmissionHandler() = default;
  auto Initialize(void) -> void;
  auto Run(void) -> void;

private:
  TimeUtils::MillisecondTimer *m_PeriodicTxTimer = nullptr;
};
} // namespace Incubator
#endif // INCUBATOR_USBTRANSMISSIONHANDLER_H
