cmake_minimum_required(VERSION 3.5)
project(CppUtilsTests)
set(CMAKE_C_STANDARD 99)
set (CMAKE_CXX_STANDARD 14)

set(TEST_FILES GeometryUtilsTest.cpp catch.hpp
        ../Point.h
        ../Circle.h
        ../RoundedRect.h
        ../MathUtils.h
        ../GeometryUtils.h StringsTest.cpp
        ../RoundedRect.h
        ../Line.h
        ../Strings.h AlgorithmsTest.cpp ../Algorithms.h ../Rect.h)
add_executable(Tests ${TEST_FILES} ../Rect.h)