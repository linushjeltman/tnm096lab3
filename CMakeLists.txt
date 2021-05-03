cmake_minimum_required(VERSION 3.17)
project(tnm096lab3)

set(CMAKE_CXX_STANDARD 14)

include_directories(lab3tnm096)

add_executable(tnm096lab3
        lab3tnm096/Clause.cpp
        lab3tnm096/clause.h
        lab3tnm096/Source.cpp)
