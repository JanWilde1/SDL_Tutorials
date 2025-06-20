cmake_minimum_required(VERSION 3.31)
project(SDL_Tutorials)

set(CMAKE_C_STANDARD 23)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${CMAKE_HOME_DIRECTORY}/include)

add_executable(SDL_Tutorials src/main.cpp)

target_link_libraries(SDL_Tutorials ${SDL2_LIBRARIES})