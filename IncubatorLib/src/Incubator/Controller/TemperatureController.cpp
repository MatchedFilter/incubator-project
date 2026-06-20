#include "Incubator/Controller/TemperatureController.h"

namespace Incubator
{
TemperatureController::TemperatureController()
    : m_bIsTemperatureValid(false), m_DesiredTemperatureInMilliCelcius(0),
      m_PreviousTemperatureInMilliCelcius(0), m_PConstant(0), m_IConstant(0), m_DConstant(0)
{
}

TemperatureController::~TemperatureController()
{
}

void TemperatureController::SetDesiredTemperature(const int32_t &desiredTemperatureInMilliCelcius)
{
  m_DesiredTemperatureInMilliCelcius = desiredTemperatureInMilliCelcius;
}

void TemperatureController::SetPid(const int32_t &p, const int32_t &i, const int32_t &d)
{
  m_PConstant = p;
  m_IConstant = i;
  m_DConstant = d;
}

uint16_t TemperatureController::Control(const int32_t &temperatureInMilliCelcius,
                                        const uint64_t &timeDifferenceInMillisecond)
{
  uint16_t result = static_cast<uint16_t>(0UL);

  if (false == m_bIsTemperatureValid)
  {
    m_PreviousTemperatureInMilliCelcius = temperatureInMilliCelcius;
    m_bIsTemperatureValid               = true;
  }

  const int32_t error = m_DesiredTemperatureInMilliCelcius - temperatureInMilliCelcius;
  constexpr int32_t THRESHOLD_TEMPERATURE_LOW_DIFFERENCE_IN_MILLICELCIUS  = 5000;
  constexpr int32_t THRESHOLD_TEMPERATURE_HIGH_DIFFERENCE_IN_MILLICELCIUS = -1000;
  if (error > THRESHOLD_TEMPERATURE_LOW_DIFFERENCE_IN_MILLICELCIUS)
  {
    result = MAX_TEMPERATURE_OUTPUT_CONTROL_VALUE;
  }
  else if (error > THRESHOLD_TEMPERATURE_HIGH_DIFFERENCE_IN_MILLICELCIUS)
  {
    const int32_t previousError =
      m_DesiredTemperatureInMilliCelcius - m_PreviousTemperatureInMilliCelcius;
    const int32_t output =
      (m_PConstant * error) +
      (m_IConstant * error * static_cast<int32_t>(timeDifferenceInMillisecond)) +
      (m_DConstant * ((error - previousError) / static_cast<int32_t>(timeDifferenceInMillisecond)));

    if (output > 0.0)
    {
      if (output < static_cast<uint16_t>(MAX_TEMPERATURE_OUTPUT_CONTROL_VALUE))
      {
        result = static_cast<uint16_t>(output);
      }
      else
      {
        result = MAX_TEMPERATURE_OUTPUT_CONTROL_VALUE;
      }
    }
  }
  else
  {
    // intentionally left blank
  }

  return result;
}

void TemperatureController::OnTemperatureFailure()
{
  m_bIsTemperatureValid               = false;
  m_PreviousTemperatureInMilliCelcius = 0.0;
}

} // namespace Incubator
