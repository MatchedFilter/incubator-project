#ifndef INCUBATOR_TEMPERATURELASTDAYSDATASETSCREEN_H
#define INCUBATOR_TEMPERATURELASTDAYSDATASETSCREEN_H
#include "ATemperatureDataSetScreen.h"
#include "Incubator/Lcd2004.h"

namespace Incubator
{
class TemperatureLastDaysDataSetScreen : public ATemperatureDataSetScreen
{
public:
  TemperatureLastDaysDataSetScreen();
  ~TemperatureLastDaysDataSetScreen();

protected:
  virtual uint32_t GetCurrentTemperatureInMilliCelcius() const final override;
  virtual uint32_t GetChangedTemperatureInMilliCelcius() const final override;
  virtual void
  SetChangedTemperatureInMilliCelcius(const uint32_t temperatureInMilliCelcius) final override;
};
} // namespace Incubator

#endif // INCUBATOR_TEMPERATURELASTDAYSDATASETSCREEN_H
