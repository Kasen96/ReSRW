cmake_minimum_required(VERSION 3.17)
project(ReSRW)

set(CMAKE_CXX_STANDARD 11)

add_executable(ReSRW resrw.cpp)

# compiler optimization turned off
# set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -O0 -g")

# compiler optimization turned on
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -O2 -g")

# Analysis
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -save-temps")
