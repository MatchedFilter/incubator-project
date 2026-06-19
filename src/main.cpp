#include "Incubator/IncubatorApp.h"
#include "Incubator/Lcd2004.h"
#include "TimeUtils/TimerManager.h"
#include "bsp_config.h"

int main(void)
{
  bsp_initialize();
  static Incubator::IncubatorApp application;
  application.Initialize();
  Incubator::Lcd2004::Initialize();

  while (1)
  {
    application.Run();
    TimeUtils::TimerManager::Run();
    Incubator::Lcd2004::Run();
  }
  return 0;
}
