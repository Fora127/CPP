cmake_minimum_required(VERSION 3.5)

project(AlarmY LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ~/sma/Builds)


add_executable(AlarmY
  main.cpp
  Controller.h
  ParamReceiver.h
  Timer.h
  ParamReceiver.cpp
  Controller.cpp

)
