#ifndef INCUBATOR_INTERNALFLASHMODEL_H
#define INCUBATOR_INTERNALFLASHMODEL_H
#include "IModel.h"

namespace Incubator
{
class InternalFlashModel : public IModel
{
public:
  InternalFlashModel();
  ~InternalFlashModel();
  virtual bool Update(const AdminData &data) override;
  virtual bool Update(const SettingsData &data) override;
  virtual bool Update(const TimeInformationData &data) override;
  virtual bool Get(AdminData &data) override;
  virtual bool Get(SettingsData &data) override;
  virtual bool Get(TimeInformationData &data) override;

private:
  const uint32_t m_FlashBaseAddress = static_cast<uint32_t>(0x0801F400UL);
};
} // namespace Incubator

#endif // INCUBATOR_INTERNALFLASHMODEL_H
