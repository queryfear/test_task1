cmake_minimum_required(VERSION 3.21)
project(test_task)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Debug
set(CMAKE_BUILD_TYPE Debug)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

message("\n\nPATH: ${PROJECT_SOURCE_DIR}\n\n")
message("\n\nPATH SOURCE DIR: ${CMAKE_SOURCE_DIR}\n\n")

file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cxx"
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})

# Debug
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-g")