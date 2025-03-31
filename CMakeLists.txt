cmake_minimum_required(VERSION 3.10)
project(KinematicVisualizer C)

set(CMAKE_C_STANDARD 99)

# Output binary in a clean place
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Source files - make this a regular console application
add_executable(kinematic src/main.c)

# Include paths for SDL2 and SDL2_ttf
include_directories(
    ${PROJECT_SOURCE_DIR}/libs/SDL2/include
    ${PROJECT_SOURCE_DIR}/libs/SDL2/include/SDL2
    ${PROJECT_SOURCE_DIR}/libs/SDL2_ttf/include
    ${PROJECT_SOURCE_DIR}/libs/SDL2_ttf/include/SDL2
)

# Link directories - tell the compiler where to find the libraries
link_directories(
    ${PROJECT_SOURCE_DIR}/libs/SDL2/lib
    ${PROJECT_SOURCE_DIR}/libs/SDL2_ttf/lib
)

# Don't use SDL_main
add_definitions(-DSDL_MAIN_HANDLED)

# Link the specific library files
target_link_libraries(kinematic
    ${PROJECT_SOURCE_DIR}/libs/SDL2/lib/libSDL2.dll.a
    ${PROJECT_SOURCE_DIR}/libs/SDL2_ttf/lib/libSDL2_ttf.dll.a
)