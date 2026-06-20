#ifndef INCUBATOR_APIDDATASETSCREEN_H
#define INCUBATOR_APIDDATASETSCREEN_H
#include "ADataSetScreen.h"
#include "Incubator/Lcd2004.h"

namespace Incubator
{
class APidDataSetScreen : public ADataSetScreen
{
public:
  APidDataSetScreen(const EnumScreenType screenType);
  ~APidDataSetScreen();

protected:
  virtual int32_t GetCurrentValue() const           = 0;
  virtual int32_t GetChangedValue() const           = 0;
  virtual void SetChangedValue(const int32_t value) = 0;

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
  static constexpr int32_t MAX_ALLOWED_CONSTANT    = static_cast<int32_t>(5000L);
  static constexpr int32_t MIN_ALLOWED_CONSTANT    = static_cast<int32_t>(-5000L);
  static constexpr int32_t HIGH_INCREMENT_CONSTANT = static_cast<uint32_t>(20L);
  static constexpr int32_t LOW_INCREMENT_CONSTANT  = static_cast<uint32_t>(1L);
};
} // namespace Incubator

#endif // INCUBATOR_APIDDATASETSCREEN_H
