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
        -specs=nosys.specs
        -T${CMAKE_CURRENT_SOURCE_DIR}/bsp/src/STM32F103C8Tx_FLASH.ld
    )

    add_compile_definitions(USE_HAL_DRIVER STM32F103xB)

    add_subdirectory(bsp)
    add_subdirectory(Common/MFBufferLib)
    add_subdirectory(Common/MFByteStreamLib)
    add_subdirectory(Common/MFEndianUtilsLib)
    add_subdirectory(IncubatorLib)

    file(GLOB_RECURSE INCUBATOR_SRCS
        src/*.cpp
    )

    add_executable(${PROJECT_NAME}.elf
        ${INCUBATOR_SRCS}
    )

    target_link_libraries(${PROJECT_NAME}.elf PRIVATE
        incubator_bsp_lib
        IncubatorLib
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
