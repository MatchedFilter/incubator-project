#ifndef BSP_BME280_H
#define BSP_BME280_H

#include <stdbool.h>
#include <stdint.h>

#define BME280_I2C_ADDRESS_LOW  (0x76U << 1)
#define BME280_I2C_ADDRESS_HIGH (0x77U << 1)
#define BME280_DEFAULT_ADDRESS  BME280_I2C_ADDRESS_LOW

/* Public Driver Interface for bsp_config.c wrappers */
bool __bsp_bme280_init(void);
void __bsp_bme280_process(void);
void __bsp_bme280_set_ready(void);

bool __bsp_bme280_get_humidity(uint8_t *humidity_percentage);
bool __bsp_bme280_get_temperature(int32_t *temperature_in_millidegree);

#endif /* BSP_BME280_H */
