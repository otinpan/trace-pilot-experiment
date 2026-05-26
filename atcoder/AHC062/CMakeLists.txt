cmake_minimum_required(VERSION 3.16)

project(AHC062 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ahc062
    src/main.cpp
    src/logger.cpp
    src/simulator.cpp
    src/state.cpp
    src/strategy/strategy.cpp
    src/strategy/greedy.cpp
)

target_include_directories(ahc062 PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)

set_target_properties(ahc062 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)

add_executable(common_test
    tests/common_test.cpp
)

target_include_directories(common_test PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)

set_target_properties(common_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)

add_executable(greedy_test
    tests/greedy_test.cpp
    src/logger.cpp
    src/state.cpp
    src/strategy/strategy.cpp
    src/strategy/greedy.cpp
)

target_include_directories(greedy_test PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)

set_target_properties(greedy_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)
