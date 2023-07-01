cmake_minimum_required(VERSION 3.0)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(sdl2-template C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(CMAKE_BUILD_TYPE Debug)

add_executable(demo main.c)
target_include_directories(demo PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(demo ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

file(COPY ${PROJECT_SOURCE_DIR}/tex.png DESTINATION ${PROJECT_BINARY_DIR})

