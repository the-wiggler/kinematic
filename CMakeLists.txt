cmake_minimum_required(VERSION 3.10)
project(KinematicVisualizer C)

set(CMAKE_C_STANDARD 99)

# Output binary in a clean place
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Source files
add_executable(kinematic src/main.c)

# Include paths for SDL2 and SDL2_ttf (from local folders)
include_directories(
    ${PROJECT_SOURCE_DIR}/libs/SDL2/include
    ${PROJECT_SOURCE_DIR}/libs/SDL2/include/SDL2
    ${PROJECT_SOURCE_DIR}/libs/SDL2_ttf/include
    ${PROJECT_SOURCE_DIR}/libs/SDL2_ttf/include/SDL2
)


# Link directories
link_directories(
    ${PROJECT_SOURCE_DIR}/libs/SDL2/lib
    ${PROJECT_SOURCE_DIR}/libs/SDL2_ttf/lib
)

# Link libraries
target_link_libraries(kinematic
    SDL2
    SDL2_ttf
)