cmake_minimum_required(VERSION 3.24)

project(aoc23)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
add_subdirectory(lib/Catch2)

include(CTest)
include(Catch)

add_subdirectory(lib/helper)

add_subdirectory(Day0)
add_subdirectory(Day1)
add_subdirectory(Day2)
add_subdirectory(Day3)
add_subdirectory(Day4)
add_subdirectory(Day5)
add_subdirectory(Day6)
add_subdirectory(Day7)

add_subdirectory(Day8)

add_subdirectory(Day9)

add_subdirectory(Day10)

add_subdirectory(Day11)

add_subdirectory(Day12)
add_subdirectory(Day13)
add_subdirectory(Day14)
add_subdirectory(Day15)