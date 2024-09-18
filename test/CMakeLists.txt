cmake_minimum_required(VERSION 3.14)
project(weatherTests)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

# Include directories
include_directories(../include ../cpp-httplib)

enable_testing()

add_executable(
  weather_test
  weather_test.cpp
  ../src/weather.cpp
)
target_link_libraries(
  weather_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(weather_test)
