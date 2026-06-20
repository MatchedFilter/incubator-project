#ifndef INCUBATOR_IDATASETSCREEN_H
#define INCUBATOR_IDATASETSCREEN_H
#include "APidDataSetScreen.h"

namespace Incubator
{
class IDataSetScreen : public APidDataSetScreen
{
public:
  IDataSetScreen();
  ~IDataSetScreen();

protected:
  virtual int32_t GetCurrentValue() const override;
  virtual int32_t GetChangedValue() const override;
  virtual void SetChangedValue(const int32_t value) override;
};
} // namespace Incubator

#endif // INCUBATOR_IDATASETSCREEN_H
