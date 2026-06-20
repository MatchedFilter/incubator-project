#ifndef INCUBATOR_TEMPERATURECONTROLLER_H
#define INCUBATOR_TEMPERATURECONTROLLER_H
#include <cstdint>
namespace Incubator
{

constexpr uint16_t MAX_TEMPERATURE_OUTPUT_CONTROL_VALUE = static_cast<uint16_t>(1000UL);

class TemperatureController
{
public:
  TemperatureController();
  ~TemperatureController();
  void SetDesiredTemperature(const int32_t &desiredTemperatureInMilliCelcius);
  void SetPid(const int32_t &p, const int32_t &i, const int32_t &d);
  uint16_t Control(const int32_t &temperatureInCelcius,
                   const uint64_t &timeDifferenceInMillisecond);
  void OnTemperatureFailure();

private:
  bool m_bIsTemperatureValid;
  int32_t m_DesiredTemperatureInMilliCelcius;
  int32_t m_PreviousTemperatureInMilliCelcius;
  int32_t m_PConstant;
  int32_t m_IConstant;
  int32_t m_DConstant;
};
} // namespace Incubator

#endif // INCUBATOR_TEMPERATURECONTROLLER_H
