#ifndef INCUBATOR_INCUBATORAPP_H
#define INCUBATOR_INCUBATORAPP_H
#include "TimeUtils/MillisecondTimer.h"
namespace Incubator
{
class IncubatorApp
{
public:
  IncubatorApp()  = default;
  ~IncubatorApp() = default;
  void Initialize();
  void Run();

private:
  TimeUtils::MillisecondTimer *m_Timer             = nullptr;
  TimeUtils::MillisecondTimer *m_HeartbeatUsbTimer = nullptr;
};
} // namespace Incubator
#endif // INCUBATOR_INCUBATORAPP_H
