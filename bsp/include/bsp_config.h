#ifndef BSP_CONFIG_H
#define BSP_CONFIG_H
#include <stdbool.h>
#include <stdint.h>

#define BSP_SERVO_MOTOR_DIRECTION_STOP  (0U)
#define BSP_SERVO_MOTOR_DIRECTION_RIGHT (1U)
#define BSP_SERVO_MOTOR_DIRECTION_LEFT  (2U)

#define BSP_LCD_2004_CHAR_LOWER_I       (0x00U)
#define BSP_LCD_2004_CHAR_LOWER_U       (0x01U)
#define BSP_LCD_2004_CHAR_LOWER_O       (0x02U)
#define BSP_LCD_2004_CHAR_LOWER_G       (0x03U)
#define BSP_LCD_2004_CHAR_LOWER_C       (0x04U)
#define BSP_LCD_2004_CHAR_UPPER_O       (0x05U)
#define BSP_LCD_2004_CHAR_DEGREE_SYMBOL (0xDFU)
#define BSP_LCD_2004_CHAR_ARROW_SYMBOL  (0x7EU)

#ifdef __cplusplus
extern "C"
{
#endif
  void bsp_initialize(void);
  void bsp_reset(void);
  void bsp_assert(bool condition);
  uint64_t bsp_get_time_in_ms(void);
  void bsp_internal_led_turn_on(void);
  void bsp_internal_led_turn_off(void);
  void bsp_internal_led_toggle(void);
  void bsp_delay_in_millisecond(const uint32_t millisecond);
  bool bsp_is_usb_data_ready(void);
  void bsp_clear_usb_data_ready(void);
  const uint8_t *bsp_get_usb_data(uint32_t *buffer_length);
  bool bsp_usb_send_data(const uint8_t *const buffer, const uint16_t size);

  void bsp_humidity_motor_turn_on(void);
  void bsp_humidity_motor_turn_off(void);

  void bsp_servo_motor_rotate(const uint8_t direction, uint8_t speedInPercentage);

  void bsp_joystick_read_positions(uint16_t *x_value, uint16_t *y_value);
  bool bsp_joystick_is_switch_pressed(void);

  void bsp_lcd_20x4_send_command(uint8_t cmd);
  void bsp_lcd_20x4_send_data(uint8_t data);
  void bsp_lcd_20x4_process_run(void);

  bool bsp_flash_write(uint32_t base_address, uint32_t offset, const uint32_t *words,
                       uint8_t words_length);

  void bsp_flash_read(const uint32_t base_address, uint32_t offset, uint32_t *words,
                      uint8_t words_length);

#ifdef __cplusplus
}
#endif

#endif /* BSP_CONFIG_H */
