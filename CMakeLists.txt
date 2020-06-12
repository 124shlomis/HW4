cmake_minimum_required(VERSION 3.16)
project(HW4)

set(CMAKE_CXX_STANDARD 11)

include_directories(files)

add_executable(HW4
        files/mini_gui.cpp
        files/mini_gui.h
        files/ascii_objects.h
        files/drawable.h
        files/drawable.cpp
        files/drawable_list.h
        files/drawable_list.cpp
        files/apple.h
        files/main.cpp)
