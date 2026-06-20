#ifndef INCUBATOR_AHYSTERISISHUMIDITYDATASETSCREEN_H
#define INCUBATOR_AHYSTERISISHUMIDITYDATASETSCREEN_H
#include "ADataSetScreen.h"
#include "Incubator/Lcd2004.h"

namespace Incubator
{
class AHysterisisHumidityDataSetScreen : public ADataSetScreen
{
public:
  AHysterisisHumidityDataSetScreen(const EnumScreenType screenType);
  ~AHysterisisHumidityDataSetScreen();

protected:
  virtual uint8_t GetCurrentDifference() const                 = 0;
  virtual uint8_t GetChangedDifference() const                 = 0;
  virtual void SetChangedDifference(const uint8_t &difference) = 0;

protected:
  virtual void PrintCurrentData() const final override;
  virtual void PrintNewData() const final override;
  virtual void OnIncrementHighEvent() final override;
  virtual void OnIncrementLowEvent() final override;
  virtual void OnDecrementHighEvent() final override;
  virtual void OnDecrementLowEvent() final override;
  virtual void NotifyChangedData() final override;
  virtual EnumScreenType GetNextScreenForYesSelection() const final override;
  virtual EnumScreenType GetNextScreenForNoSelection() const final override;

private:
  static constexpr uint8_t MAX_ALLOWED_CONSTANT    = 45U;
  static constexpr uint8_t MIN_ALLOWED_CONSTANT    = 1U;
  static constexpr uint8_t HIGH_INCREMENT_CONSTANT = 10U;
  static constexpr uint8_t LOW_INCREMENT_CONSTANT  = 1U;
};
} // namespace Incubator

#endif // INCUBATOR_AHYSTERISISHUMIDITYDATASETSCREEN_H
