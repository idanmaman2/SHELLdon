cmake_minimum_required(VERSION 3.23)
project(IDSH C)

set(CMAKE_C_STANDARD 23)

add_executable(IDSH main.c vector.h shellprinting.h stack.h)
