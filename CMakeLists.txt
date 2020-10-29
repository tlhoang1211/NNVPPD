cmake_minimum_required(VERSION 3.15)
project(Scanner C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Scanner
        main.c
        scanner.c
        scanner.h)
