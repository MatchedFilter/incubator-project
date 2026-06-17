#ifndef TIMEUTILS_MILLISECONDTIMER_H
#define TIMEUTILS_MILLISECONDTIMER_H
#include "bsp_config.h"

#include <cstdint>
namespace TimeUtils
{
class MillisecondTimer
{
public:
  inline void SetDuration(const std::uint32_t durationInMs)
  {
    m_Duration = durationInMs;
  }

  inline void Start()
  {
    m_IsRunning = true;
    m_StartTime = bsp_get_time_in_ms();
  }

  inline void Stop()
  {
    m_IsRunning = false;
  }

  inline bool IsFinished(void) const
  {
    return !m_IsRunning;
  }

  inline void Update(const uint32_t currentTimeInMillisecond)
  {
    if (m_IsRunning)
    {
      const bool is_valid = !(currentTimeInMillisecond < m_StartTime);
      if (is_valid)
      {
        const bool is_finished = !((currentTimeInMillisecond - m_StartTime) < m_Duration);
        if (is_finished)
        {
          m_IsRunning = false;
        }
      }
      else
      {
        m_IsRunning = false;
      }
    }
  }

private:
  MillisecondTimer()        = default;
  ~MillisecondTimer()       = default;
  std::uint32_t m_Duration  = 0U;
  std::uint32_t m_StartTime = 0U;
  bool m_IsRunning          = false;
  friend class TimerManager;
};
} // namespace TimeUtils
#endif // TIMEUTILS_MILLISECONDTIMER_H
