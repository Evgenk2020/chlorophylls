cmake_minimum_required(VERSION 3.2)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
#SET(CMAKE_BUILD_TYPE Debug)

SET(CMAKE_BUILD_RPATH app)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BUILD_RPATH}/lib)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BUILD_RPATH}/bin)

project(chloro LANGUAGES CXX)

add_library(chlo STATIC chloro.h chloro.cpp output.h output.cpp)

add_executable(chloro main.cpp)
target_link_libraries(chloro chlo)
