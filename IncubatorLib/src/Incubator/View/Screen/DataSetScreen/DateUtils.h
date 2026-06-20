#ifndef INCUBATOR_DATEUTILS_H
#define INCUBATOR_DATEUTILS_H
#include <cstdint>
namespace Incubator
{
class DateUtils
{
public:
  static uint8_t GetDayFromTimestamp(const uint32_t &timeStampInSecond);
  static uint8_t GetHourFromTimestamp(const uint32_t &timeStampInSecond);
  static uint8_t GetMinuteFromTimestamp(const uint32_t &timeStampInSecond);
  static uint8_t GetSecondFromTimestamp(const uint32_t &timeStampInSecond);
  static uint32_t GetTimestapmInSecondFromDate(const uint8_t &day, const uint8_t &hour,
                                               const uint8_t &minute, const uint8_t &second);
};
} // namespace Incubator

#endif // INCUBATOR_DATEUTILS_H
