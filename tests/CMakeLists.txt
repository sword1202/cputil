cmake_minimum_required(VERSION 3.5)
project(CppUtilsTests)
set(CMAKE_C_STANDARD 99)
set (CMAKE_CXX_STANDARD 11)

set(TEST_FILES GeometryUtilsTest.cpp catch.hpp ../GeometryUtils.h)
add_executable(Tests ${TEST_FILES})