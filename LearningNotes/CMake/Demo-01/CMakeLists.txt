cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(Demo-01 LANGUAGES CXX)

#if (MSVC)
#execute_process(
#    COMMAND execute_process.bat 
#    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
#endif()

find_program(ANT_PATH NAMES "ant.bat")
message(STATUS "ANT_PATH: ${ANT_PATH}")

execute_process(COMMAND ant.bat "-version" 
                RESULT_VARIABLE result
                OUTPUT_VARIABLE output
                ERROR_VARIABLE error)

message(STATUS "result: ${result}")
message(STATUS "output: ${output}")
message(STATUS "error: ${error}")


find_program(JAVE_PATH NAMES java)
message(STATUS "JAVE_PATH: ${JAVE_PATH}")

execute_process(COMMAND java --version  
                RESULT_VARIABLE result
                OUTPUT_VARIABLE output
                ERROR_VARIABLE error)

message(STATUS "result: ${result}")
message(STATUS "output: ${output}")
message(STATUS "error: ${error}")

find_program(GIT_PATH NAMES git)
message(STATUS "GIT_PATH: ${GIT_PATH}")

execute_process(COMMAND ${GIT_PATH} --version  
                RESULT_VARIABLE result
                OUTPUT_VARIABLE output
                ERROR_VARIABLE error)

message(STATUS "result: ${result}")
message(STATUS "output: ${output}")
message(STATUS "error: ${error}")

#execute_process(
#    COMMAND "C:/Program Files/Git/git-bash.exe" execute_process.sh 
#    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

execute_process(
    COMMAND bash execute_process.sh 
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error)
message(STATUS "result: ${result}")
message(STATUS "output: ${output}")
message(STATUS "error: ${error}")

add_executable(Demo-01 HelloWorld.cpp)