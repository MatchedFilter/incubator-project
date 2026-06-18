#include "bsp_config.h"

#include "cmsis_gcc.h"
#include "main.h"
#include "stm32f103xb.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_i2c.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

#define SERVO_CENTER_PULSE (1020)

I2C_HandleTypeDef hi2c1;
volatile bool usb_data_ready   = false;
volatile uint32_t usb_rx_len   = 0U;
uint8_t usb_rx_buffer[64]      = {0U};
volatile bool usb_port_is_open = false;
extern volatile uint32_t systick_counter;

DMA_HandleTypeDef hdma_i2c1_rx;
DMA_HandleTypeDef hdma_i2c1_tx;
TIM_HandleTypeDef htim2;

void SystemClock_Config(void);
static void gpio_init(void);
static void dma_init(void);
static void internal_led_init(void);
static void force_usb_reenumeration(void);
static void i2c1_init(void);
static void tim2_init(void);
static void pwm_init(void);

void bsp_initialize(void)
{
  HAL_Init();
  SystemClock_Config();
  internal_led_init();
  gpio_init();
  dma_init();
  i2c1_init();
  tim2_init();
  pwm_init();
  HAL_Delay(2000U);
  force_usb_reenumeration();
  MX_USB_DEVICE_Init();
}

void bsp_reset(void)
{
  NVIC_SystemReset();
}

void bsp_assert(bool condition)
{
  if (condition == false)
  {
    Error_Handler();
  }
}

uint32_t bsp_get_time_in_ms(void)
{
  return systick_counter;
}

void bsp_internal_led_turn_on(void)
{
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
}

void bsp_internal_led_turn_off(void)
{
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
}

void bsp_internal_led_toggle(void)
{
  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}

void bsp_delay_in_millisecond(const uint32_t millisecond)
{
  HAL_Delay(millisecond);
}

bool bsp_is_usb_data_ready(void)
{
  return usb_data_ready;
}

void bsp_clear_usb_data_ready(void)
{
  usb_data_ready = false;
}

const uint8_t *bsp_get_usb_data(uint32_t *const buffer_length)
{
  uint8_t *result = NULL;
  if (usb_data_ready == true)
  {
    result         = &usb_rx_buffer[0];
    *buffer_length = usb_rx_len;
  }
  return result;
}

bool bsp_usb_send_data(const uint8_t *const buffer, const uint16_t size)
{
  bool result = false;
  if (usb_port_is_open)
  {
    result = (CDC_Transmit_FS((uint8_t *) buffer, size) == USBD_OK);
  }
  return result;
}

void bsp_humidity_motor_turn_on(void)
{
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
}

void bsp_humidity_motor_turn_off(void)
{
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
}

void bsp_servo_motor_rotate(const uint8_t direction, uint8_t speedInPercentage)
{
  if (speedInPercentage > 100U)
  {
    speedInPercentage = 100U;
  }

  uint32_t ccr_value = SERVO_CENTER_PULSE;

  switch (direction)
  {
    case BSP_SERVO_MOTOR_DIRECTION_RIGHT:
      ccr_value = SERVO_CENTER_PULSE + (speedInPercentage * 10U);
      break;

    case BSP_SERVO_MOTOR_DIRECTION_LEFT:
      ccr_value = SERVO_CENTER_PULSE - (speedInPercentage * 10U);
      break;

    case BSP_SERVO_MOTOR_DIRECTION_STOP:
    default:
      ccr_value = SERVO_CENTER_PULSE;
      break;
  }

  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, ccr_value);
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct   = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct   = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState       = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState       = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL     = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  RCC_ClkInitStruct.ClockType =
    RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection    = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
    for (uint8_t i = 0U; i < 2U; i++)
    {
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
      HAL_Delay(2000);
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
      HAL_Delay(2000);
    }

    for (uint8_t i = 0U; i < 10U; i++)
    {
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
      HAL_Delay(100);
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
      HAL_Delay(100);
    }
  }
}

static void gpio_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
  GPIO_InitStruct.Pin   = GPIO_PIN_4 | GPIO_PIN_7;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static void dma_init(void)
{
  __HAL_RCC_DMA1_CLK_ENABLE();
  HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
  HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);
}

static void internal_led_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOC_CLK_ENABLE();
  GPIO_InitStruct.Pin   = GPIO_PIN_13;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP; // Push-Pull mode
  GPIO_InitStruct.Pull  = GPIO_NOPULL;         // No internal resistors
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // Low frequency safe layout
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

static void force_usb_reenumeration(void)
{
  __HAL_RCC_GPIOA_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin              = GPIO_PIN_12;
  GPIO_InitStruct.Mode             = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed            = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
  HAL_Delay(250);

  HAL_GPIO_DeInit(GPIOA, GPIO_PIN_12);
  __HAL_RCC_USB_CLK_ENABLE();
  USB->ISTR = 0;
  NVIC_ClearPendingIRQ(USB_LP_CAN1_RX0_IRQn);
}

static void i2c1_init(void)
{
  hi2c1.Instance             = I2C1;
  hi2c1.Init.ClockSpeed      = 100000;
  hi2c1.Init.DutyCycle       = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1     = 0;
  hi2c1.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2     = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
}

static void tim2_init(void)
{
  TIM_SlaveConfigTypeDef sSlaveConfig   = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC          = {0};
  htim2.Instance                        = TIM2;
  htim2.Init.Prescaler                  = 71;
  htim2.Init.CounterMode                = TIM_COUNTERMODE_UP;
  htim2.Init.Period                     = 19999;
  htim2.Init.ClockDivision              = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload          = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sSlaveConfig.SlaveMode    = TIM_SLAVEMODE_DISABLE;
  sSlaveConfig.InputTrigger = TIM_TS_ITR0;
  if (HAL_TIM_SlaveConfigSynchro(&htim2, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode     = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode     = TIM_OCMODE_PWM1;
  sConfigOC.Pulse      = SERVO_CENTER_PULSE;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_TIM_MspPostInit(&htim2);
}

static void pwm_init(void)
{
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
}
