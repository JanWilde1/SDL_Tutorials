cmake_minimum_required(VERSION 3.31)
project(SDL_Tutorial_TexLoading)

set(CMAKE_CPP_STANDARD 23)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(SDL_Tutorial_TexLoading texture-loading.cpp)

set_target_properties(SDL_Tutorial_TexLoading PROPERTIES MACOSX_BUNDLE TRUE)
file (COPY ${CMAKE_CURRENT_SOURCE_DIR}/../../res/img DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/SDL_Tutorial_TexLoading.app/Contents/Resources)

target_link_libraries(SDL_Tutorial_TexLoading SDL2::SDL2)