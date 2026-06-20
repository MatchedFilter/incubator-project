#ifndef INCUBATOR_AHUMIDITYDATASETSCREEN_H
#define INCUBATOR_AHUMIDITYDATASETSCREEN_H
#include "ADataSetScreen.h"
#include "Incubator/Lcd2004.h"

namespace Incubator
{
class AHumidityDataSetScreen : public ADataSetScreen
{
public:
  AHumidityDataSetScreen(const EnumScreenType screenType);
  ~AHumidityDataSetScreen();

protected:
  virtual uint8_t GetCurrentHumidityInPercentage() const                          = 0;
  virtual uint8_t GetChangedHumidityInPercentage() const                          = 0;
  virtual void SetChangedHumidityInPercentage(const uint8_t humidityInPercentage) = 0;

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
  static constexpr uint8_t MAX_ALLOWED_HUMIDITY_IN_PERCENTAGE = 100U;
  static constexpr uint8_t MIN_ALLOWED_HUMIDITY_IN_PERCENTAGE = 20U;
  static constexpr uint8_t HIGH_INCREMENT_IN_PERCENTAGE       = 10U;
  static constexpr uint8_t LOW_INCREMENT_IN_PERCENTAGE        = 1U;
};
} // namespace Incubator

#endif // INCUBATOR_AHUMIDITYDATASETSCREEN_H
