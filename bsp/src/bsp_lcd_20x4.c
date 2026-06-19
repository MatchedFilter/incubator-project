#include "bsp_lcd_20x4.h"

#include "stm32f1xx_hal.h"

#include <stdbool.h>

#define LCD_BUFFER_SIZE 512U
#define LCD_BUFFER_MASK (LCD_BUFFER_SIZE - 1U)

/* PCF8574 to HD44780 Pin Mapping */
#define LCD_PIN_RS          (1U << 0)
#define LCD_PIN_RW          (1U << 1)
#define LCD_PIN_EN          (1U << 2)
#define LCD_PIN_BACKLIGHT   (1U << 3)
#define PCF8574_I2C_ADDRESS (0x27 << 1)

/* Raw 512-byte circular storage */
static uint8_t lcd_ring_buffer[LCD_BUFFER_SIZE];
static volatile uint16_t head_index = 0U;
static volatile uint16_t tail_index = 0U;
static volatile bool queue_is_full  = false;

/* Timing and State Machine */
typedef enum
{
  LCD_STATE_IDLE,
  LCD_STATE_WAIT_EXECUTION
} LcdState_t;

static LcdState_t lcd_state     = LCD_STATE_IDLE;
static uint32_t delay_target_us = 0U;
static uint32_t delay_start_us  = 0U;

extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim3;

static uint32_t get_us_ticks(void);

static uint32_t get_us_ticks(void)
{
  return __HAL_TIM_GET_COUNTER(&htim3);
}

static void ring_buffer_push_raw(uint8_t raw_byte);
static void lcd_send_nibble_blocking(uint8_t nibble);
static void enqueue_lcd_byte(uint8_t data, uint8_t control_flags);

void __bsp_lcd_20x4_send_command(uint8_t cmd)
{
  enqueue_lcd_byte(cmd, LCD_PIN_BACKLIGHT);
}

void __bsp_lcd_20x4_send_data(uint8_t data)
{
  enqueue_lcd_byte(data, LCD_PIN_BACKLIGHT | LCD_PIN_RS);
}

void __bsp_lcd_20x4_process_queue(void)
{
  switch (lcd_state)
  {
    case LCD_STATE_IDLE:
    {
      if ((head_index == tail_index) && !queue_is_full)
      {
        return;
      }

      uint8_t check_byte         = lcd_ring_buffer[tail_index];
      uint32_t execution_time_us = 40U;

      if (check_byte == (0x00 | LCD_PIN_BACKLIGHT | LCD_PIN_EN))
      {
        // Double-check the next byte configuration to confirm it's a Clear command
        uint8_t next_check = lcd_ring_buffer[(tail_index + 1U) & LCD_BUFFER_MASK];
        if (next_check == (0x00 | LCD_PIN_BACKLIGHT))
        {
          execution_time_us = 1600U; // Clear Screen detected
        }
      }

      delay_target_us = 400U + execution_time_us;
      delay_start_us  = get_us_ticks();

      if ((tail_index + 4U) <= LCD_BUFFER_SIZE)
      {
        if (HAL_I2C_Master_Transmit_DMA(&hi2c1, PCF8574_I2C_ADDRESS, &lcd_ring_buffer[tail_index],
                                        4U) == HAL_OK)
        {
          tail_index    = (tail_index + 4U) & LCD_BUFFER_MASK;
          queue_is_full = false;
          lcd_state     = LCD_STATE_WAIT_EXECUTION;
        }
      }
      else
      {
        static uint8_t bounce_buffer[4];
        for (uint8_t i = 0U; i < 4U; i++)
        {
          bounce_buffer[i] = lcd_ring_buffer[(tail_index + i) & LCD_BUFFER_MASK];
        }

        if (HAL_I2C_Master_Transmit_DMA(&hi2c1, PCF8574_I2C_ADDRESS, bounce_buffer, 4U) == HAL_OK)
        {
          tail_index    = (tail_index + 4U) & LCD_BUFFER_MASK;
          queue_is_full = false;
          lcd_state     = LCD_STATE_WAIT_EXECUTION;
        }
      }
      break;
    }

    case LCD_STATE_WAIT_EXECUTION:
    {
      // Ensure I2C peripheral is completely free and timing window has satisfied
      if (HAL_I2C_GetState(&hi2c1) == HAL_I2C_STATE_READY)
      {
        uint32_t current_us = get_us_ticks();
        uint32_t elapsed_us = 0U;

        if (current_us >= delay_start_us)
        {
          elapsed_us = current_us - delay_start_us;
        }
        else
        {
          // TIM3 has a 16-bit ARR period wrap around adjustment
          elapsed_us = (htim3.Init.Period - delay_start_us) + current_us;
        }

        if (elapsed_us >= delay_target_us)
        {
          lcd_state = LCD_STATE_IDLE;
        }
      }
      break;
    }
  }
}

void __bsp_lcd_20x4_initialize(void)
{
  HAL_TIM_Base_Start(&htim3);

  HAL_Delay(50U);

  // --- STEP 1: Hardware-Level 4-Bit Reset Sequence ---
  // Must be executed as raw individual nibbles while the controller is in 8-bit mode
  lcd_send_nibble_blocking(0x30U);
  HAL_Delay(5U);

  lcd_send_nibble_blocking(0x30U);
  HAL_Delay(2U);

  lcd_send_nibble_blocking(0x30U);
  HAL_Delay(1U);

  lcd_send_nibble_blocking(0x20U); // Interface finally drops to 4-bit configuration
  HAL_Delay(1U);

  // --- STEP 2: Main HD44780 Configurations ---
  // 0x28 = 4-bit interface, 4 rows (or 2 physical lines internally), 5x8 font
  // 0x0C = Display completely ON, Cursor line OFF, Cursor blink OFF
  // 0x01 = Clear display screen RAM data map
  // 0x06 = Entry state mode: Automatic text shift right increment
  uint8_t init_cmds[] = {0x28U, 0x0CU, 0x01U, 0x06U};

  for (uint8_t i = 0U; i < sizeof(init_cmds); i++)
  {
    uint8_t upper = init_cmds[i] & 0xF0;
    uint8_t lower = (init_cmds[i] << 4) & 0xF0;

    uint8_t seq[4] = {upper | LCD_PIN_BACKLIGHT | LCD_PIN_EN, upper | LCD_PIN_BACKLIGHT,
                      lower | LCD_PIN_BACKLIGHT | LCD_PIN_EN, lower | LCD_PIN_BACKLIGHT};

    HAL_I2C_Master_Transmit(&hi2c1, PCF8574_I2C_ADDRESS, seq, 4U, 100U);

    // Clear display instruction (0x01) mandates a longer layout cycle execution time
    HAL_Delay(init_cmds[i] == 0x01U ? 2U : 1U);
  }
}

static void enqueue_lcd_byte(uint8_t data, uint8_t control_flags)
{
  uint8_t upper_nibble = data & 0xF0U;
  uint8_t lower_nibble = (data << 4U) & 0xF0U;

  ring_buffer_push_raw(upper_nibble | control_flags | LCD_PIN_EN);
  ring_buffer_push_raw(upper_nibble | control_flags);
  ring_buffer_push_raw(lower_nibble | control_flags | LCD_PIN_EN);
  ring_buffer_push_raw(lower_nibble | control_flags);
}

static void ring_buffer_push_raw(uint8_t raw_byte)
{
  if (!queue_is_full)
  {
    lcd_ring_buffer[head_index] = raw_byte;
    head_index                  = (head_index + 1U) & LCD_BUFFER_MASK;

    if (head_index == tail_index)
    {
      queue_is_full = true;
    }
  }
}

static void lcd_send_nibble_blocking(uint8_t nibble)
{
  uint8_t raw[2] = {nibble | LCD_PIN_BACKLIGHT | LCD_PIN_EN, nibble | LCD_PIN_BACKLIGHT};
  HAL_I2C_Master_Transmit(&hi2c1, PCF8574_I2C_ADDRESS, raw, 2U, 100U);
}
