#ifndef TIMEUTILS_MILLISECONDTIMER_H
#define TIMEUTILS_MILLISECONDTIMER_H
#include "bsp_config.h"

#include <cstdint>
namespace TimeUtils
{
class MillisecondTimer
{
public:
  inline auto SetDuration(const std::uint32_t durationInMs) -> void
  {
    m_Duration = durationInMs;
  }

  inline auto Start()
  {
    m_IsFinished = false;
    m_IsRunning  = true;
    m_StartTime  = bsp_get_time_in_ms();
  }

  inline auto Stop()
  {
    m_IsRunning  = false;
    m_IsFinished = false;
  }

  inline auto IsFinished(void) const
  {
    return m_IsFinished;
  }

  inline auto IsRunning(void) const
  {
    return m_IsRunning;
  }

  inline auto Update(const uint64_t currentTimeInMillisecond)
  {
    if (m_IsRunning)
    {
      const bool is_valid = !(currentTimeInMillisecond < m_StartTime);
      if (is_valid)
      {
        const bool is_finished =
          !((currentTimeInMillisecond - m_StartTime) < static_cast<uint64_t>(m_Duration));
        if (is_finished)
        {
          m_IsFinished = true;
          m_IsRunning  = false;
        }
      }
      else
      {
        m_IsFinished = true;
        m_IsRunning  = false;
      }
    }
  }

private:
  MillisecondTimer()        = default;
  ~MillisecondTimer()       = default;
  std::uint32_t m_Duration  = 0U;
  std::uint64_t m_StartTime = 0U;
  bool m_IsRunning          = false;
  bool m_IsFinished         = false;
  friend class TimerManager;
};
} // namespace TimeUtils
#endif // TIMEUTILS_MILLISECONDTIMER_H
