cmake_minimum_required(VERSION 3.10)
project(ScheduleEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(scheduler
        src/main.cpp
        src/io.cpp
        src/models.h
        src/io.h
        src/io.cpp
        src/greedy_scheduler.h
        src/greedy_scheduler.cpp


)

target_include_directories(scheduler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
