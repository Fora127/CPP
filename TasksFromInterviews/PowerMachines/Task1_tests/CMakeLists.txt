cmake_minimum_required(VERSION 3.5)

project(AlarmY_Tests LANGUAGES CXX)


find_package(Qt5Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

add_executable(AlarmY_Tests
    tst_alarmy_tests.cpp
    ../Task1/Controller.cpp
    )
add_test(NAME AlarmY_Tests COMMAND AlarmY_Tests)

target_link_libraries(AlarmY_Tests PRIVATE Qt5::Test)

