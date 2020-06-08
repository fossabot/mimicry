if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "DO NOT BUILD in-tree.")
endif()

# set compile options
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# project definition
cmake_minimum_required(VERSION 3.14)
project(mimicry VERSION 0.0.0 DESCRIPTION "Minicry, cross-compile graphical framework")

option(BUILD_LIBDEBUG "Enable building libdebug.a" ON)

# required modules for our task
include(third_party.cmake)

add_executable(
  ${PROJECT_NAME} 
  src/main.cpp
)

# if(BUILD_LIBDEBUG)
#   add_subdirectory(lib/debug)
# endif()

add_dependencies(
  ${PROJECT_NAME} 
  SDL2-project
)

target_link_libraries(
  ${PROJECT_NAME} 
  SDL2
)

add_dependencies(
  ${PROJECT_NAME} 
  skia-project
)

target_link_libraries(
  ${PROJECT_NAME} 
  skia
)

# # Uncomment for tests
# include(CTest)
# enable_testing()

# if(BUILD_TESTING)
#     add_subdirectory (tests)
# endif()