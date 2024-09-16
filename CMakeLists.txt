cmake_minimum_required(VERSION 3.10)
project(weather_server)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include cpp-httplib)

# Add the executable
add_executable(weather main.cpp src/weather.cpp)
