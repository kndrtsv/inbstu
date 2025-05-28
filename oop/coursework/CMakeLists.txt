cmake_minimum_required(VERSION 3.27)
project(coursework)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(coursework
        main.cpp
        sqlite3.c
        sqlite3.h
        transaction.h
        transaction_factory.h)
