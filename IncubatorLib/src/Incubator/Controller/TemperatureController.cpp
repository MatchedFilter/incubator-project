#include "Incubator/Controller/TemperatureController.h"

namespace Incubator
{
TemperatureController::TemperatureController()
    : m_bIsTemperatureValid(false), m_DesiredTemperatureInCelcius(0.0),
      m_PreviousTemperatureInCelcius(0.0), m_PConstant(0.0), m_IConstant(0.0), m_DConstant(0.0)
{
}

TemperatureController::~TemperatureController()
{
}

void TemperatureController::SetDesiredTemperature(const double &desiredTemperatureInCelcius)
{
  m_DesiredTemperatureInCelcius = desiredTemperatureInCelcius;
}

void TemperatureController::SetPid(const double &p, const double &i, const double &d)
{
  m_PConstant = p * 10.0;
  m_IConstant = i * 400.0;
  m_DConstant = d / 25.0;
}

uint16_t TemperatureController::Control(const double &temperatureInCelcius,
                                        const uint64_t &timeDifferenceInMillisecond)
{
  uint16_t result = static_cast<uint16_t>(0UL);

  const double timeDifferenceInSeconds = static_cast<double>(timeDifferenceInMillisecond) / 1000.0;
  if (false == m_bIsTemperatureValid)
  {
    m_PreviousTemperatureInCelcius = temperatureInCelcius;
    m_bIsTemperatureValid          = true;
  }

  const double error = m_DesiredTemperatureInCelcius - temperatureInCelcius;
  constexpr double THRESHOLD_TEMPERATURE_LOW_DIFFERENCE_IN_MILLICELCIUS  = 5.0;
  constexpr double THRESHOLD_TEMPERATURE_HIGH_DIFFERENCE_IN_MILLICELCIUS = -1.0;
  if (error > THRESHOLD_TEMPERATURE_LOW_DIFFERENCE_IN_MILLICELCIUS)
  {
    result = MAX_TEMPERATURE_OUTPUT_CONTROL_VALUE;
  }
  else if (error > THRESHOLD_TEMPERATURE_HIGH_DIFFERENCE_IN_MILLICELCIUS)
  {
    const double previousError = m_DesiredTemperatureInCelcius - m_PreviousTemperatureInCelcius;
    const double output = (m_PConstant * error) + (m_IConstant * error * timeDifferenceInSeconds) +
                          (m_DConstant * ((error - previousError) / timeDifferenceInSeconds));

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
  m_bIsTemperatureValid          = false;
  m_PreviousTemperatureInCelcius = 0.0;
}

} // namespace Incubator
