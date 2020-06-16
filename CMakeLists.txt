cmake_minimum_required(VERSION 3.16)
project(HW4)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(HW4
        main.cpp
        ascii_objects.h
        mini_gui.cpp
        mini_gui.h
        drawable.h
        drawable.cpp
        drawable_list.h
        drawable_list.cpp
        apple.h
        apple.cpp
        monster.h
        test_drawable_list_module.h
        test_drawable_list_module.cpp )
