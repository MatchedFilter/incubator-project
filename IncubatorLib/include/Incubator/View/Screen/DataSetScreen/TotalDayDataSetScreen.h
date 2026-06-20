#ifndef INCUBATOR_TOTALDAYDATASETSCREEN_H
#define INCUBATOR_TOTALDAYDATASETSCREEN_H
#include "ADataSetScreen.h"
#include "Incubator/Lcd2004.h"

namespace Incubator
{
class TotalDayDataSetScreen : public ADataSetScreen
{
public:
  TotalDayDataSetScreen();
  ~TotalDayDataSetScreen();

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
  static constexpr uint8_t MAX_ALLOWED_DAY_COUNT = 60U;
  static constexpr uint8_t MIN_ALLOWED_DAY_COUNT = 0U;
  static constexpr uint8_t HIGH_INCREMENT_COUNT  = 10U;
  static constexpr uint8_t LOW_INCREMENT_COUNT   = 1U;

private:
  void SetSecondFromDayCount(const uint8_t &dayCount);
  void PrintDayString(const uint8_t day) const;
};
} // namespace Incubator

#endif // INCUBATOR_TOTALDAYDATASETSCREEN_H
