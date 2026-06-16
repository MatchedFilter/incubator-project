#ifndef BSP_CONFIG_H
#define BSP_CONFIG_H
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif
  void bsp_initialize(void);
  void internal_led_turn_on(void);
  void internal_led_turn_off(void);
  void internal_led_toggle(void);
  void delay_in_millisecond(const uint32_t millisecond);

#ifdef __cplusplus
}
#endif

#endif /* BSP_CONFIG_H */
