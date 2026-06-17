#include "Incubator/IncubatorApp.h"
#include "TimeUtils/TimerManager.h"
#include "bsp_config.h"

int main(void)
{
  bsp_initialize();
  static Incubator::IncubatorApp application;
  application.Initialize();

  while (1)
  {
    application.Run();
    TimeUtils::TimerManager::Run();
  }
  return 0;
}
