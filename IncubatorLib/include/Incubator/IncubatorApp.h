#ifndef INCUBATOR_INCUBATORAPP_H
#define INCUBATOR_INCUBATORAPP_H
#include "Incubator/IncubatorData/SensorsStatusData.h"
#include "Incubator/Model/InternalFlashModel.h"
#include "Incubator/Presenter/Presenter.h"
#include "Incubator/View/Lcd2004View.h"
#include "TimeUtils/MillisecondTimer.h"
#include "UsbCommandHandler.h"
#include "UsbTransmissionHandler.h"

namespace Incubator
{
class IncubatorApp
{
public:
  IncubatorApp()  = default;
  ~IncubatorApp() = default;
  auto Initialize(void) -> void;
  auto Run(void) -> void;

private:
  Presenter m_Presenter;
  Lcd2004View m_Lcd2004View;
  InternalFlashModel m_InternalFlashModel;
  TimeUtils::MillisecondTimer *m_Timer = nullptr;
  UsbCommandHandler m_UsbCommandHandler;
  UsbTransmissionHandler m_UsbTransmissionHandler;
};
} // namespace Incubator
#endif // INCUBATOR_INCUBATORAPP_H
