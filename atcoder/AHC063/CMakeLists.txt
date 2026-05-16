cmake_minimum_required(VERSION 3.16)

project(atcoder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    src/stage.cpp
    src/snake.cpp
    src/state.cpp
    src/simulator.cpp
    src/logger.cpp
    src/experiment_logger.cpp
    src/strategy/strategy.cpp
    src/strategy/greedy.cpp
    src/strategy/hill_climbing.cpp
    src/strategy/simulated_annealing.cpp
)

add_executable(main
    src/main.cpp
    ${SOURCES}
)

target_include_directories(main PRIVATE "${CMAKE_SOURCE_DIR}/src")


# Place the built executable in the repository's build directory.
set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)

enable_testing()

add_executable(common_test tests/common_test.cpp)
target_include_directories(common_test PRIVATE "${CMAKE_SOURCE_DIR}/src")

add_test(NAME common_test COMMAND common_test)

set_target_properties(common_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)

add_executable(stage_test tests/stage_test.cpp src/stage.cpp)
target_include_directories(stage_test PRIVATE "${CMAKE_SOURCE_DIR}/src")

add_test(NAME stage_test COMMAND stage_test)

set_target_properties(stage_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)

add_executable(snake_test tests/snake_test.cpp src/snake.cpp)
target_include_directories(snake_test PRIVATE "${CMAKE_SOURCE_DIR}/src")

add_test(NAME snake_test COMMAND snake_test)

set_target_properties(snake_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)

add_executable(state_test tests/state_test.cpp src/state.cpp src/stage.cpp src/snake.cpp src/logger.cpp)
target_include_directories(state_test PRIVATE "${CMAKE_SOURCE_DIR}/src")

add_test(NAME state_test COMMAND state_test)

set_target_properties(state_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)

find_package(Python3 COMPONENTS Interpreter REQUIRED)

add_custom_target(submit_cpp
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/scripts/gen_submit.py" --output "${CMAKE_SOURCE_DIR}/submit.cpp"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    COMMENT "Generating submit.cpp"
)
