#include "TimeUtils/TimeSettings.h"

#include "bsp_config.h"

namespace TimeUtils
{
uint32_t s_IncubatorTimeStampInSecond                   = 0U;
static uint64_t s_IncubatorTimestampOffsetInMillisecond = 0U;

auto TimeSettings::GetIncubatorTimeInSeconds(void) -> uint32_t
{
  const uint32_t result =
    s_IncubatorTimeStampInSecond +
    static_cast<uint32_t>(bsp_get_time_in_ms() - s_IncubatorTimestampOffsetInMillisecond) /
      static_cast<uint32_t>(1000UL);
  return result;
}
auto TimeSettings::SetIncubatorTimeInSeconds(uint32_t sec) -> void
{
  s_IncubatorTimeStampInSecond            = sec;
  s_IncubatorTimestampOffsetInMillisecond = bsp_get_time_in_ms();
}
} // namespace TimeUtils
