#include "TimeUtils/TimerManager.h"

#include "TimeUtils/MillisecondTimer.h"
#include "bsp_config.h"

namespace TimeUtils
{
uint8_t TimerManager::s_Index = 0;
MillisecondTimer TimerManager::s_Timers[MAX_MS_TIMER_SIZE];

auto TimerManager::CreateMillisecondTimer(void) -> MillisecondTimer *
{
  MillisecondTimer *timer = nullptr;
  if (s_Index < MAX_MS_TIMER_SIZE) [[likely]]
  {
    timer = &s_Timers[s_Index];
    s_Index++;
  }
  else
  {
    bsp_assert(false);
  }
  return timer;
}

auto TimerManager::Run(void) -> void
{
  const uint64_t currentMs = bsp_get_time_in_ms();
  for (uint8_t i = 0U; i < s_Index; i++)
  {
    s_Timers[i].Update(currentMs);
  }
}

} // namespace TimeUtils
