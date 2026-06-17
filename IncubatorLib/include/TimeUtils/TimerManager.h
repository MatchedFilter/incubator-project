#ifndef TIMEUTILS_TIMERMANAGER_H
#define TIMEUTILS_TIMERMANAGER_H
#include "TimeUtils/MillisecondTimer.h"

#include <cstdint>
namespace TimeUtils
{

class TimerManager
{
public:
  TimerManager()  = delete;
  ~TimerManager() = delete;
  static MillisecondTimer *CreateMillisecondTimer(void);
  static void Run(void);

private:
  static uint8_t s_Index;
  static constexpr uint8_t MAX_MS_TIMER_SIZE = 8U;
  static MillisecondTimer s_Timers[MAX_MS_TIMER_SIZE];
};
} // namespace TimeUtils
#endif // TIMEUTILS_TIMERMANAGER_H
