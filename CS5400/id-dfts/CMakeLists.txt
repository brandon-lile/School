cmake_minimum_required(VERSION 3.3)
project(id_dfts)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES driver.cpp driver.h tree.cpp tree.h node.cpp node.h)
add_executable(id_dfts ${SOURCE_FILES})