#ifndef INCUBATOR_TEMPERATUREDATASETSCREEN_H
#define INCUBATOR_TEMPERATUREDATASETSCREEN_H
#include "ATemperatureDataSetScreen.h"
#include "Incubator/Lcd2004.h"

namespace Incubator
{
class TemperatureDataSetScreen : public ATemperatureDataSetScreen
{
public:
  TemperatureDataSetScreen();
  ~TemperatureDataSetScreen();

protected:
  virtual uint32_t GetCurrentTemperatureInMilliCelcius() const final override;
  virtual uint32_t GetChangedTemperatureInMilliCelcius() const final override;
  virtual void
  SetChangedTemperatureInMilliCelcius(const uint32_t temperatureInMilliCelcius) final override;
};
} // namespace Incubator

#endif // INCUBATOR_TEMPERATUREDATASETSCREEN_H
