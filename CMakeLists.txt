cmake_minimum_required(VERSION 3.10)
project(PowerSimCore VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

find_package(GTest REQUIRED)
include(GoogleTest)

file(GLOB_RECURSE TEST_SOURCES "test/*.cpp")
add_executable(PowerSimTests ${TEST_SOURCES} ${SOURCES})

target_link_libraries(PowerSimTests PRIVATE GTest::gtest GTest::gtest_main)

enable_testing()
gtest_discover_tests(PowerSimTests)
