cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(Demo-01 LANGUAGES CXX)

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
  add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
  add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

add_executable(Demo-01 main.cpp)