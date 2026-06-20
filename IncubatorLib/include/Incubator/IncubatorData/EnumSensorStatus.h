#ifndef INCUBATOR_ENUMSENSORSTATUS_H
#define INCUBATOR_ENUMSENSORSTATUS_H
#include <cinttypes>
namespace Incubator
{
enum EnumSensorStatus : uint8_t
{
  SENSOR_STATUS_ERROR    = 0U,
  SENSOR_STATUS_NO_ERROR = 1U
};
} // namespace Incubator

#endif // INCUBATOR_ENUMSENSORSTATUS_H
