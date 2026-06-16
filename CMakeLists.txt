cmake_minimum_required(VERSION 3.22)
project(incubator-project C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_C_FLAGS_RELEASE "-Os -flto -fdata-sections -ffunction-sections" CACHE STRING "" FORCE)
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-Wl,--gc-sections -flto" CACHE STRING "" FORCE)
    add_compile_options(
        -mcpu=cortex-m3
        -mthumb
        -Wall
        -Wextra
        -fdata-sections
        -ffunction-sections
        -Os
        -flto
    )

    add_link_options(
        -mcpu=cortex-m3
        -mthumb
        -specs=nano.specs
        -Wl,--gc-sections
        -flto
        -Wl,-Map=${PROJECT_NAME}.map,--cref
        -T${CMAKE_CURRENT_SOURCE_DIR}/bsp/src/STM32F103C8Tx_FLASH.ld
    )

    add_compile_definitions(USE_HAL_DRIVER STM32F103xB)

    include_directories(
        include
        bsp/src/Drivers/STM32F1xx_HAL_Driver/Inc
        bsp/src/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy
        bsp/src/Drivers/CMSIS/Device/ST/STM32F1xx/Include
        bsp/src/Drivers/CMSIS/Include
        bsp/src/Core/Inc
        bsp/src/Middlewares/ST/STM32_USB_Device_Library/Core/Inc
        bsp/src/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc
        bsp/src/USB_DEVICE/App
        bsp/src/USB_DEVICE/Target
        bsp/include
    )

    file(GLOB_RECURSE SOURCES 
        "src/*.cpp"
        "bsp/src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c"
        "bsp/src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c"
        "bsp/src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c"
        "bsp/src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c"
        "bsp/src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c"
        "bsp/src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c"
        "bsp/src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c"
        "bsp/src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c"
        "bsp/src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c"
        "bsp/src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pcd.c"
        "bsp/src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pcd_ex.c"
        "bsp/src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_i2c.c"
        "bsp/src/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_usb.c"

        "bsp/src/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c"
        "bsp/src/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c"
        "bsp/src/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c"
        "bsp/src/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c"

        "bsp/src/USB_DEVICE/App/usb_device.c"
        "bsp/src/USB_DEVICE/App/usbd_cdc_if.c"
        "bsp/src/USB_DEVICE/App/usbd_desc.c"
        "bsp/src/USB_DEVICE/Target/usbd_conf.c"

        "bsp/src/Core/Src/*.c"
        "bsp/src/Core/Src/*.s"
        "bsp/src/bsp_config.c"
    )


    set_source_files_properties(bsp/Core/Src/startup_stm32f103xb.s
        PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp"
    )

    add_executable(${PROJECT_NAME}.elf
        ${SOURCES}
        ${COMMON_SRCS}
    )

    add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
        COMMAND ${CMAKE_OBJCOPY} -O srec ${PROJECT_NAME}.elf ${PROJECT_NAME}.srec
        COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf
        COMMENT "Generating auxiliary flash memory file formats (.bin, .hex, .srec)..."
    )



else()
    message(STATUS "Linux build not implemented yet!")
endif()


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
