cmake_minimum_required(VERSION 3.12...3.27)

project(ProcessScheduling
        VERSION 0.1
        DESCRIPTION "Simulation of different process scheduling strategies"
        LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(scheduling 
                src/ArgumentHandler.cpp
                src/Process.cpp
                src/schedulingStrategy.cpp
                src/SJF.cpp
                src/EDF.cpp
                src/FCFS.cpp
                src/LLF.cpp
                src/RoundRobin.cpp)

target_include_directories(scheduling 
        PUBLIC 
        include)