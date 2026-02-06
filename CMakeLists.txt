cmake_minimum_required(VERSION 4.0)
project(WinDozer)

set(CMAKE_CXX_STANDARD 26)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")

add_library(WinDozer STATIC WinDozer.cpp WinDozer.h)

add_executable(windozer_test WIN32 test.cpp)
target_link_libraries(windozer_test PRIVATE WinDozer user32 gdi32 kernel32)