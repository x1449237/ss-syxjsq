cmake_minimum_required(VERSION 3.20)

project(syxjsq)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(syxjsq
        src/main.cpp
        src/calculator.cpp
        src/date_calculator.cpp
        src/history.cpp
)