#ifndef INCUBATOR_SENSORSSTATUSDATA_H
#define INCUBATOR_SENSORSSTATUSDATA_H
#include "EnumSensorStatus.h"

namespace Incubator
{
struct SensorsStatusData
{
public:
  EnumSensorStatus m_Bme280Status;

  inline void Reset()
  {
    m_Bme280Status = SENSOR_STATUS_ERROR;
  }

  inline void Copy(const SensorsStatusData &other)
  {
    m_Bme280Status = other.m_Bme280Status;
  }
};
} // namespace Incubator

#endif // INCUBATOR_SENSORSSTATUSDATA_H
