#ifndef INCUBATOR_PDATASETSCREEN_H
#define INCUBATOR_PDATASETSCREEN_H
#include "APidDataSetScreen.h"

namespace Incubator
{
class PDataSetScreen : public APidDataSetScreen
{
public:
  PDataSetScreen();
  ~PDataSetScreen();

protected:
  virtual int32_t GetCurrentValue() const override;
  virtual int32_t GetChangedValue() const override;
  virtual void SetChangedValue(const int32_t value) override;
};
} // namespace Incubator

#endif // INCUBATOR_PDATASETSCREEN_H
