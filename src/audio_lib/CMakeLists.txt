cmake_minimum_required(VERSION 3.16)
project(AMSR_AUDIO C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_library(
        AMSR

        src/main/amsr_instance.c
)
