cmake_minimum_required(VERSION 3.10)
project(HighPerformanceWebServer)

set(CMAKE_CXX_STANDARD 17)

# Include headers from include/
include_directories(include)

# Source files
file(GLOB SOURCES
    src/*.cpp
    main.cpp
)

add_executable(webserver ${SOURCES})
