#ifndef BSP_LCD_20X4_H
#define BSP_LCD_20X4_H
#include <stdint.h>

void __bsp_lcd_20x4_send_command(uint8_t cmd);
void __bsp_lcd_20x4_send_data(uint8_t data);
void __bsp_lcd_20x4_process_queue(void);
void __bsp_lcd_20x4_initialize(void);

#endif /* BSP_LCD_20X4_H */
