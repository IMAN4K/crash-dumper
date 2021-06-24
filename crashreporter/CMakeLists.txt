cmake_minimum_required(VERSION 3.1)

project(TEST)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

find_package(benchmark REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    benchmark::benchmark
    )
