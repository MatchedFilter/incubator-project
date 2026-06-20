#ifndef TIMEUTILS_TIMESETTINGS_H
#define TIMEUTILS_TIMESETTINGS_H
#include <cstdint>
namespace TimeUtils
{
class TimeSettings
{
public:
  TimeSettings() = delete;
  static auto GetIncubatorTimeInSeconds(void) -> uint32_t;
  static auto SetIncubatorTimeInSeconds(uint32_t sec) -> void;
};
} // namespace TimeUtils
#endif // TIMEUTILS_TIMESETTINGS_H
