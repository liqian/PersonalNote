cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(Demo-01 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED On)

FIND_PACKAGE(Threads)

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
  add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
  add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

add_executable(Demo-01 main.cpp)

TARGET_LINK_LIBRARIES(Demo-01 ${CMAKE_THREAD_LIBS_INIT})