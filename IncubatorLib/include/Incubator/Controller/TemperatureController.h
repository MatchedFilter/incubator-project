#ifndef INCUBATOR_TEMPERATURECONTROLLER_H
#define INCUBATOR_TEMPERATURECONTROLLER_H
#include <cinttypes>
namespace Incubator
{

constexpr uint16_t MAX_TEMPERATURE_OUTPUT_CONTROL_VALUE = static_cast<uint16_t>(1000UL);

class TemperatureController
{
public:
  TemperatureController();
  ~TemperatureController();
  void SetDesiredTemperature(const double &desiredTemperatureInCelcius);
  void SetPid(const double &p, const double &i, const double &d);
  uint16_t Control(const double &temperatureInCelcius, const uint64_t &timeDifferenceInMillisecond);
  void OnTemperatureFailure();

private:
  bool m_bIsTemperatureValid;
  double m_DesiredTemperatureInCelcius;
  double m_PreviousTemperatureInCelcius;
  double m_PConstant;
  double m_IConstant;
  double m_DConstant;
};
} // namespace Incubator

#endif // INCUBATOR_TEMPERATURECONTROLLER_H
