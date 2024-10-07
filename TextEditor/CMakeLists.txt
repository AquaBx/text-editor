cmake_minimum_required(VERSION 3.29)
project(TextEditor)

set(CMAKE_CXX_STANDARD 26)

add_subdirectory(libs/SDL)
include_directories(libs/SDL/include)

add_subdirectory(libs/SDL_ttf)
include_directories(libs/SDL_ttf)

add_executable(TextEditor WIN32 main.cpp)
target_link_libraries(TextEditor SDL SDL_ttf)
