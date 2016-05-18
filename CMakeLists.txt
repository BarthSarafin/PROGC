cmake_minimum_required(VERSION 3.3)
project(PROGC_bachmste_greutnic)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES PROGC_Praktikum/PROGC_C_P5/selbststudium/main.c)
add_executable(PROGC_bachmste_greutnic ${SOURCE_FILES})