#include "bsp_config.h"

int main(void)
{
  bsp_initialize();
  while (1)
  {
    internal_led_turn_on();
    delay_in_millisecond(5000U);
    internal_led_turn_off();
    delay_in_millisecond(2000U);
  }
  return 0;
}
