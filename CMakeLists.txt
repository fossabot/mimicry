if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "DO NOT BUILD in-tree.")
endif()

# set compile options
set(CMAKE_CXX_STANDARD 14)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fPIC")
endif()

# project definition
cmake_minimum_required(VERSION 3.17)
project(mimicry VERSION 0.0.0 DESCRIPTION "Minicry, cross-compile graphical framework")

option(BUILD_LIBDEBUG "Enable building libdebug.a" ON)

add_subdirectory(externals)

add_executable(
  ${PROJECT_NAME} 
  src/main.cpp
)

add_dependencies(
  ${PROJECT_NAME} 
  SDL2
  skia
)

target_link_libraries(
  ${PROJECT_NAME} 
  PRIVATE
  SDL2
  skia
)

target_include_directories(
  ${PROJECT_NAME} 
  PRIVATE 
  externals/skia
  externals/skia/include/core
  externals/SDL/include
)

# if(BUILD_LIBDEBUG)
#   add_subdirectory(lib/debug)
# endif()




# # Uncomment for tests
# include(CTest)
# enable_testing()

# if(BUILD_TESTING)
#     add_subdirectory (tests)
# endif()