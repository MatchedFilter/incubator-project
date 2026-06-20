#ifndef INCUBATOR_LOWERHYSTERISISHUMIDITYDATASETSCREEN_H
#define INCUBATOR_LOWERHYSTERISISHUMIDITYDATASETSCREEN_H
#include "AHysterisisHumidityDataSetScreen.h"

namespace Incubator
{
class LowerHysterisisHumidityDataSetScreen : public AHysterisisHumidityDataSetScreen
{
public:
  LowerHysterisisHumidityDataSetScreen();
  ~LowerHysterisisHumidityDataSetScreen();

protected:
  virtual uint8_t GetCurrentDifference() const override;
  virtual uint8_t GetChangedDifference() const override;
  virtual void SetChangedDifference(const uint8_t &difference) override;
};
} // namespace Incubator

#endif // INCUBATOR_LOWERHYSTERISISHUMIDITYDATASETSCREEN_H
