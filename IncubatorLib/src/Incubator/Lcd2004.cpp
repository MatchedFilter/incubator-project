#include "Incubator/Lcd2004.h"

#include "TimeUtils/MillisecondTimer.h"
#include "TimeUtils/TimerManager.h"
#include "bsp_config.h"

namespace Incubator
{

TimeUtils::MillisecondTimer *s_LcdTimer = nullptr;

auto Lcd2004::Initialize(void) -> void
{
  s_LcdTimer = TimeUtils::TimerManager::CreateMillisecondTimer();
  s_LcdTimer->SetDuration(3000U);
  s_LcdTimer->Start();
}

auto Lcd2004::Print(const uint8_t specialChar) -> void
{
  bsp_lcd_20x4_send_data(specialChar);
}

auto Lcd2004::Run(void) -> void
{
  if (s_LcdTimer->IsFinished())
  {
    s_LcdTimer->Start();
  }
  bsp_lcd_20x4_process_run();
}

} // namespace Incubator
