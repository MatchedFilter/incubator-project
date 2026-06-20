#ifndef INCUBATOR_DDATASETSCREEN_H
#define INCUBATOR_DDATASETSCREEN_H
#include "APidDataSetScreen.h"

namespace Incubator
{
class DDataSetScreen : public APidDataSetScreen
{
public:
  DDataSetScreen();
  ~DDataSetScreen();

protected:
  virtual int32_t GetCurrentValue() const override;
  virtual int32_t GetChangedValue() const override;
  virtual void SetChangedValue(const int32_t value) override;
};
} // namespace Incubator

#endif // INCUBATOR_DDATASETSCREEN_H
