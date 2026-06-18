cmake_minimum_required(VERSION 3.22)
project(incubator_bsp_lib C ASM)

add_compile_definitions(USE_HAL_DRIVER STM32F103xB)

file(GLOB_RECURSE INCUBATOR_BSP_LIB_SRCS
    "src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c"
    "src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c"
    "src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c"
    "src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c"
    "src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c"
    "src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c"
    "src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c"
    "src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c"
    "src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c"
    "src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pcd.c"
    "src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pcd_ex.c"
    "src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_i2c.c"
    "src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c"
    "src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c"
    "src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_usb.c"

    "src/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c"
    "src/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c"
    "src/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c"
    "src/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c"

    "src/USB_DEVICE/App/usb_device.c"
    "src/USB_DEVICE/App/usbd_cdc_if.c"
    "src/USB_DEVICE/App/usbd_desc.c"
    "src/USB_DEVICE/Target/usbd_conf.c"

    "src/Core/Src/*.c"
    "src/Core/Src/*.s"
    "src/bsp_config.c"
)

set_source_files_properties(Core/Src/startup_stm32f103xb.s
    PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp"
)

add_library(${PROJECT_NAME} STATIC
    ${INCUBATOR_BSP_LIB_SRCS}
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    src/Drivers/STM32F1xx_HAL_Driver/Inc
    src/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy
    src/Drivers/CMSIS/Device/ST/STM32F1xx/Include
    src/Drivers/CMSIS/Include
    src/Core/Inc
    src/Middlewares/ST/STM32_USB_Device_Library/Core/Inc
    src/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc
    src/USB_DEVICE/App
    src/USB_DEVICE/Target
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

