#ifndef INCUBATOR_UPPERHYSTERISISHUMIDITYDATASETSCREEN_H
#define INCUBATOR_UPPERHYSTERISISHUMIDITYDATASETSCREEN_H
#include "AHysterisisHumidityDataSetScreen.h"

namespace Incubator
{
class UpperHysterisisHumidityDataSetScreen : public AHysterisisHumidityDataSetScreen
{
public:
  UpperHysterisisHumidityDataSetScreen();
  ~UpperHysterisisHumidityDataSetScreen();

protected:
  virtual uint8_t GetCurrentDifference() const override;
  virtual uint8_t GetChangedDifference() const override;
  virtual void SetChangedDifference(const uint8_t &difference) override;
};
} // namespace Incubator

#endif // INCUBATOR_UPPERHYSTERISISHUMIDITYDATASETSCREEN_H
