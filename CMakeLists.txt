cmake_minimum_required(VERSION 3.16)
project(HW4)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(HW4
        ascii_objects.h
        mini_gui.h
        mini_gui.cpp
        drawable.h
        drawable.cpp
        drawable_list.h
        drawable_list.cpp
        apple.h
        apple.cpp
        monster.h
        monster.cpp
        main.cpp)
