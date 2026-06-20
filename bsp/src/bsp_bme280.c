#include "bsp_bme280.h"

#include "stm32f1xx_hal.h"

#include <stddef.h>

extern I2C_HandleTypeDef hi2c1;

bool sensor_error = false;

typedef struct
{
  uint16_t dig_T1;
  int16_t dig_T2;
  int16_t dig_T3;
  uint16_t dig_H1;
  int16_t dig_H2;
  uint16_t dig_H3;
  int16_t dig_H4;
  int16_t dig_H5;
  int8_t dig_H6;
} bme280_calib_t;

typedef enum
{
  BME280_STATE_IDLE,
  BME280_STATE_DMA_BUSY,
  BME280_STATE_DATA_READY
} bme280_state_t;

static bme280_calib_t bme280_calib;
static int32_t t_fine;
static volatile bme280_state_t bme_state = BME280_STATE_IDLE;

static uint8_t dma_rx_buffer[8]       = {0U};
static int32_t current_temperature_md = 0;
static uint8_t current_humidity_pct   = 0U;

/* Helper functions */
static bool bme280_read_and_parse_calib(void);
static void bme280_parse_and_compensate(void);

/**
 * @brief Confirms device ID, loads calibration, configs modes, and performs
 * an initial blocking data read to seed the metrics before DMA runs.
 */
bool __bsp_bme280_init(void)
{
  uint8_t chip_id = 0U;

  /* 1. Confirm device identity match */
  if (HAL_I2C_Mem_Read(&hi2c1, BME280_DEFAULT_ADDRESS, 0xD0U, I2C_MEMADD_SIZE_8BIT, &chip_id, 1U,
                       100U) != HAL_OK)
  {
    return false;
  }
  if (chip_id != 0x60U)
  {
    return false;
  }

  /* 2. Collect and process the factory calibration parameters */
  if (!bme280_read_and_parse_calib())
  {
    return false;
  }

  /* 3. Configure sampling profiles (Humidity x1, Temp x1, Normal Mode) */
  uint8_t ctrl_hum = 0x01U;
  if (HAL_I2C_Mem_Write(&hi2c1, BME280_DEFAULT_ADDRESS, 0xF2U, I2C_MEMADD_SIZE_8BIT, &ctrl_hum, 1U,
                        100U) != HAL_OK)
  {
    return false;
  }

  uint8_t ctrl_meas = 0x23U;
  if (HAL_I2C_Mem_Write(&hi2c1, BME280_DEFAULT_ADDRESS, 0xF4U, I2C_MEMADD_SIZE_8BIT, &ctrl_meas, 1U,
                        100U) != HAL_OK)
  {
    return false;
  }

  /* 4. Perform an initial synchronous blocking read to establish a valid baseline */
  if (HAL_I2C_Mem_Read(&hi2c1, BME280_DEFAULT_ADDRESS, 0xF7U, I2C_MEMADD_SIZE_8BIT, dma_rx_buffer,
                       8U, 100U) != HAL_OK)
  {
    return false;
  }

  /* Parse the baseline data immediately */
  bme280_parse_and_compensate();

  bme_state = BME280_STATE_IDLE;
  return true;
}

/**
 * @brief Non-blocking background scheduler to handle the dynamic state cycles.
 */
void __bsp_bme280_process(void)
{
  static uint32_t dma_timeout_counter = 0;
  switch (bme_state)
  {
    case BME280_STATE_IDLE:
      if (HAL_I2C_Mem_Read_DMA(&hi2c1, BME280_DEFAULT_ADDRESS, 0xF7U, I2C_MEMADD_SIZE_8BIT,
                               dma_rx_buffer, 8U) == HAL_OK)
      {
        bme_state = BME280_STATE_DMA_BUSY;
      }
      else
      {
        sensor_error = true;
      }
      break;

    case BME280_STATE_DATA_READY:
      bme280_parse_and_compensate();
      bme_state = BME280_STATE_IDLE;
      break;

    case BME280_STATE_DMA_BUSY:
    default:
      break;
  }

  if (bme_state == BME280_STATE_DMA_BUSY)
  {
    dma_timeout_counter++;
    if (dma_timeout_counter > 1000U)
    {
      bme_state = BME280_STATE_IDLE; // Reset state machine
    }
    dma_timeout_counter = 0;
    sensor_error        = true;

    // Trigger a custom error flag here
  }
  else
  {
    dma_timeout_counter = 0;
  }
}

void __bsp_bme280_set_ready(void)
{
  if (bme_state == BME280_STATE_DMA_BUSY)
  {
    sensor_error = false;
    bme_state    = BME280_STATE_DATA_READY;
  }
}

bool __bsp_bme280_get_humidity(uint8_t *humidity_percentage)
{
  bool result = false;
  if (!sensor_error)
  {
    if (humidity_percentage != NULL)
    {
      result               = true;
      *humidity_percentage = current_humidity_pct;
    }
  }
  return result;
}

bool __bsp_bme280_get_temperature(int32_t *temperature_in_millidegree)
{
  bool result = false;
  if (!sensor_error)
  {
    if (temperature_in_millidegree != NULL)
    {
      result                      = true;
      *temperature_in_millidegree = current_temperature_md;
    }
  }
  return result;
}

/**
 * @brief Private helper to extract out factory-programmed calibration maps.
 */
static bool bme280_read_and_parse_calib(void)
{
  uint8_t calib1[24] = {0U};
  uint8_t calib2[1]  = {0U};
  uint8_t calib3[7]  = {0U};

  if (HAL_I2C_Mem_Read(&hi2c1, BME280_DEFAULT_ADDRESS, 0x88U, I2C_MEMADD_SIZE_8BIT, calib1, 24U,
                       100U) != HAL_OK)
  {
    return false;
  }
  if (HAL_I2C_Mem_Read(&hi2c1, BME280_DEFAULT_ADDRESS, 0xA1U, I2C_MEMADD_SIZE_8BIT, calib2, 1U,
                       100U) != HAL_OK)
  {
    return false;
  }
  if (HAL_I2C_Mem_Read(&hi2c1, BME280_DEFAULT_ADDRESS, 0xE1U, I2C_MEMADD_SIZE_8BIT, calib3, 7U,
                       100U) != HAL_OK)
  {
    return false;
  }

  bme280_calib.dig_T1 = (uint16_t) ((calib1[1] << 8) | calib1[0]);
  bme280_calib.dig_T2 = (int16_t) ((calib1[3] << 8) | calib1[2]);
  bme280_calib.dig_T3 = (int16_t) ((calib1[5] << 8) | calib1[4]);
  bme280_calib.dig_H1 = calib2[0];
  bme280_calib.dig_H2 = (int16_t) ((calib3[1] << 8) | calib3[0]);
  bme280_calib.dig_H3 = calib3[2];
  bme280_calib.dig_H4 = (int16_t) ((calib3[3] << 4) | (calib3[4] & 0x0FU));
  bme280_calib.dig_H5 = (int16_t) ((calib3[5] << 4) | (calib3[4] >> 4));
  bme280_calib.dig_H6 = (int8_t) calib3[6];

  return true;
}

/**
 * @brief Common processing block used by both blocking init and asynchronous DMA cycles.
 */
static void bme280_parse_and_compensate(void)
{
  int32_t adc_T =
    (int32_t) (((uint32_t) dma_rx_buffer[3] << 12) | ((uint32_t) dma_rx_buffer[4] << 4) |
               ((uint32_t) dma_rx_buffer[5] >> 4));
  int32_t adc_H = (int32_t) (((uint32_t) dma_rx_buffer[6] << 8) | (uint32_t) dma_rx_buffer[7]);

  /* Bosch Temperature Formula Evaluation */
  int32_t var1_t =
    ((((adc_T >> 3) - ((int32_t) bme280_calib.dig_T1 << 1))) * ((int32_t) bme280_calib.dig_T2)) >>
    11;
  int32_t var2_t = (((((adc_T >> 4) - ((int32_t) bme280_calib.dig_T1)) *
                      ((adc_T >> 4) - ((int32_t) bme280_calib.dig_T1))) >>
                     12) *
                    ((int32_t) bme280_calib.dig_T3)) >>
                   14;
  t_fine         = var1_t + var2_t;

  int32_t temp_hundredths = (t_fine * 5 + 128) >> 8;
  current_temperature_md  = temp_hundredths * 10;

  /* Bosch Humidity Formula Evaluation */
  int32_t v_x1_u32r = (t_fine - ((int32_t) 76800));
  v_x1_u32r = (((((adc_H << 14) - (((int32_t) bme280_calib.dig_H4) << 20) -
                  (((int32_t) bme280_calib.dig_H5) * v_x1_u32r)) +
                 ((int32_t) 16384)) >>
                15) *
               (((((((v_x1_u32r * ((int32_t) bme280_calib.dig_H6)) >> 10) *
                    (((v_x1_u32r * ((int32_t) bme280_calib.dig_H3)) >> 11) + ((int32_t) 32768))) >>
                   10) +
                  ((int32_t) 2097152)) *
                   ((int32_t) bme280_calib.dig_H2) +
                 8192) >>
                14));
  v_x1_u32r =
    (v_x1_u32r -
     (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t) bme280_calib.dig_H1)) >> 4));
  v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
  v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);

  uint32_t hum_q10     = (uint32_t) (v_x1_u32r >> 12);
  current_humidity_pct = (uint8_t) (hum_q10 >> 10);
}
