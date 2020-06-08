cmake_minimum_required(VERSION 3.16)
project(HW4 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(HW4
        mini_gui.c
        mini_gui.h
        sample.c)
