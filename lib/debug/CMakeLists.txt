if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "DO NOT BUILD in-tree.")
endif()

# set compile options
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# project definition
cmake_minimum_required(VERSION 3.14)
project(libdebug VERSION 0.0.0 DESCRIPTION "Debug library")

add_library(
  ${PROJECT_NAME} 
  ${CMAKE_CURRENT_SOURCE_DIR}/src/debug.cpp
)

add_library(sub::debug ALIAS ${PROJECT_NAME})

target_include_directories(
  ${PROJECT_NAME} 
  PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
)
