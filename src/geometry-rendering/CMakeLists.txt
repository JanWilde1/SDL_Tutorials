cmake_minimum_required(VERSION 3.31)
project(SDL_GeometryRendering)

set(CMAKE_CXX_STANDARD 23)
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(SDL_GeometryRendering geometry-rendering.cpp)

target_link_libraries(SDL_GeometryRendering SDL2::SDL2)