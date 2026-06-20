#ifndef INCUBATOR_CURRENTMINUTEDATASETSCREEN_H
#define INCUBATOR_CURRENTMINUTEDATASETSCREEN_H
#include "ADataSetScreen.h"
#include "Incubator/Lcd2004.h"

namespace Incubator
{
class CurrentMinuteDataSetScreen : public ADataSetScreen
{
public:
  CurrentMinuteDataSetScreen();
  ~CurrentMinuteDataSetScreen();

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
  static constexpr uint8_t MAX_ALLOWED_MINUTE_COUNT = 59U;
  static constexpr uint8_t MIN_ALLOWED_MINUTE_COUNT = 0U;
  static constexpr uint8_t HIGH_INCREMENT_COUNT     = 10U;
  static constexpr uint8_t LOW_INCREMENT_COUNT      = 1U;

private:
  void SetSecondFromMinute(const uint8_t &minute);
  void PrintMinute(const uint8_t minute) const;
};
} // namespace Incubator

#endif // INCUBATOR_CURRENTMINUTEDATASETSCREEN_H
