cmake_minimum_required(VERSION 3.31)
project(SDL_TexLoading)

set(CMAKE_CXX_STANDARD 23)

find_package(SDL3 CONFIG REQUIRED)

add_executable(SDL_TexLoading texture-loading.cpp)

set_target_properties(SDL_TexLoading PROPERTIES MACOSX_BUNDLE TRUE)
file (COPY ${CMAKE_CURRENT_SOURCE_DIR}/../../res/img DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/SDL_TexLoading.app/Contents/Resources)

target_link_libraries(SDL_TexLoading SDL3::SDL3 SDL3_image::SDL3_image)