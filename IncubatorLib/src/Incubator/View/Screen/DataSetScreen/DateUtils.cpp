#include "DateUtils.h"

namespace Incubator
{

uint8_t DateUtils::GetDayFromTimestamp(const uint32_t &timeStampInSecond)
{
  return static_cast<uint8_t>(
    ((timeStampInSecond / static_cast<uint32_t>(60UL)) / static_cast<uint32_t>(60UL)) /
    static_cast<uint32_t>(24UL));
}

uint8_t DateUtils::GetHourFromTimestamp(const uint32_t &timeStampInSecond)
{
  return static_cast<uint8_t>(
    ((timeStampInSecond / static_cast<uint32_t>(60UL)) / static_cast<uint32_t>(60UL)) %
    static_cast<uint32_t>(24UL));
}

uint8_t DateUtils::GetMinuteFromTimestamp(const uint32_t &timeStampInSecond)
{
  return static_cast<uint8_t>((timeStampInSecond / static_cast<uint32_t>(60UL)) %
                              static_cast<uint32_t>(60UL));
}

uint8_t DateUtils::GetSecondFromTimestamp(const uint32_t &timeStampInSecond)
{
  return static_cast<uint8_t>(timeStampInSecond % static_cast<uint32_t>(60UL));
}

uint32_t DateUtils::GetTimestapmInSecondFromDate(const uint8_t &day, const uint8_t &hour,
                                                 const uint8_t &minute, const uint8_t &second)
{
  return (static_cast<uint32_t>(day) * static_cast<uint32_t>(60UL) * static_cast<uint32_t>(60UL) *
          static_cast<uint32_t>(24UL)) +
         (static_cast<uint32_t>(hour) * static_cast<uint32_t>(60UL) * static_cast<uint32_t>(60UL)) +
         (static_cast<uint32_t>(minute) * static_cast<uint32_t>(60UL)) +
         static_cast<uint32_t>(second);
}

} // namespace Incubator
