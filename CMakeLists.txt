cmake_minimum_required(VERSION 3.11)

project(aoc23)

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