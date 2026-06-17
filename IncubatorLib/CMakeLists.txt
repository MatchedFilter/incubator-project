cmake_minimum_required(VERSION 3.22)
project(IncubatorLib)

file(GLOB_RECURSE INCUBATOR_LIB_SRCS
    src/*.cpp
)

add_library(${PROJECT_NAME} STATIC
    ${INCUBATOR_LIB_SRCS}
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PUBLIC incubator_bsp_lib)
