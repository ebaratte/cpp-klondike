
cmake_minimum_required(VERSION 2.6)

project(KLONDIKE)

set(CMAKE_CXX_FLAGS "-std=c++11")

if (APPLE)
    set(CMAKE_CXX_COMPILER "clang++")
    set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
endif()

include_directories($(KLONDIKE_SOURCE_DIR)/src)
file(GLOB sources src/*.cpp main.cpp)
add_executable(klondike ${sources})


