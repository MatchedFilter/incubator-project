#ifndef INCUBATOR_CURRENTHOURDATASETSCREEN_H
#define INCUBATOR_CURRENTHOURDATASETSCREEN_H
#include "ADataSetScreen.h"
#include "Incubator/Lcd2004.h"

namespace Incubator
{
class CurrentHourDataSetScreen : public ADataSetScreen
{
public:
  CurrentHourDataSetScreen();
  ~CurrentHourDataSetScreen();

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
  static constexpr uint8_t MAX_ALLOWED_HOUR_COUNT = 23U;
  static constexpr uint8_t MIN_ALLOWED_HOUR_COUNT = 0U;
  static constexpr uint8_t HIGH_INCREMENT_COUNT   = 10U;
  static constexpr uint8_t LOW_INCREMENT_COUNT    = 1U;

private:
  void SetSecondFromHour(const uint8_t &hour);
  void PrintHour(const uint8_t hour) const;
};
} // namespace Incubator

#endif // INCUBATOR_CURRENTHOURDATASETSCREEN_H
