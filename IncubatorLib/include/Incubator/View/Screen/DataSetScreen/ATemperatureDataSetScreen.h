#ifndef INCUBATOR_ATEMPERATUREDATASETSCREEN_H
#define INCUBATOR_ATEMPERATUREDATASETSCREEN_H
#include "ADataSetScreen.h"
#include "Incubator/Lcd2004.h"

namespace Incubator
{
class ATemperatureDataSetScreen : public ADataSetScreen
{
public:
  ATemperatureDataSetScreen(const EnumScreenType screenType);
  ~ATemperatureDataSetScreen();

protected:
  virtual uint32_t GetCurrentTemperatureInMilliCelcius() const                               = 0;
  virtual uint32_t GetChangedTemperatureInMilliCelcius() const                               = 0;
  virtual void SetChangedTemperatureInMilliCelcius(const uint32_t temperatureInMilliCelcius) = 0;

protected:
  virtual void PrintCurrentData() const final override;
  virtual void PrintNewData() const final override;
  virtual void OnIncrementHighEvent() final override;
  virtual void OnIncrementLowEvent() final override;
  virtual void OnDecrementHighEvent() final override;
  virtual void OnDecrementLowEvent() final override;
  virtual void NotifyChangedData() final override;
  virtual EnumScreenType GetNextScreenForNoSelection() const final override;

private:
  static constexpr uint32_t MAX_ALLOWED_TEMPERATURE_IN_MILLICELCIUS =
    static_cast<uint32_t>(55000UL);
  static constexpr uint32_t MIN_ALLOWED_TEMPERATURE_IN_MILLICELCIUS =
    static_cast<uint32_t>(15000UL);
  static constexpr uint32_t HIGH_INCREMENT_IN_MILLICELCIUS = static_cast<uint32_t>(1000UL);
  static constexpr uint32_t LOW_INCREMENT_IN_MILLICELCIUS  = static_cast<uint32_t>(100UL);
};
} // namespace Incubator

#endif // INCUBATOR_ATEMPERATUREDATASETSCREEN_H
