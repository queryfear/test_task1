cmake_minimum_required(VERSION 3.21)
project(test_task)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Generating compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Debug
# set(CMAKE_BUILD_TYPE Debug)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

message("\n\nPATH: ${PROJECT_SOURCE_DIR}\n\n")
message("\n\nPATH SOURCE DIR: ${CMAKE_SOURCE_DIR}\n\n")

file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/program1.cxx" 
    "${PROJECT_SOURCE_DIR}/src/program2.cxx" 
    "${PROJECT_SOURCE_DIR}/src/ConvA.cxx" 
    "${PROJECT_SOURCE_DIR}/src/main.cxx"
)

file(GLOB_RECURSE PROGRAM1
    "${PROJECT_SOURCE_DIR}/src/program1.cxx" 
    "${PROJECT_SOURCE_DIR}/src/prog1main.cxx" 
    "${PROJECT_SOURCE_DIR}/src/ConvA.cxx" 
)

file(GLOB_RECURSE PROGRAM2
    "${PROJECT_SOURCE_DIR}/src/program1.cxx" 
    "${PROJECT_SOURCE_DIR}/src/ConvA.cxx" 
    "${PROJECT_SOURCE_DIR}/src/program2.cxx" 
    "${PROJECT_SOURCE_DIR}/src/prog2main.cxx"
)

add_executable(${PROJECT_NAME} ${SOURCES})
add_executable(prog1 ${PROGRAM1})
add_executable(prog2 ${PROGRAM2})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})

# Debug
# set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-g")
# set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-g")
# set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-g")