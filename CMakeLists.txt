cmake_minimum_required(VERSION 3.10)
project(KinematicVisualizer CXX)

set(CMAKE_CXX_STANDARD 11)

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Source files
add_executable(kinematic WIN32 src/main.cpp src/InitializePath.cpp)

# Don't use SDL_main
add_definitions(-DSDL_MAIN_HANDLED)

# Include paths (common)
include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/libs/SDL2/include
    ${PROJECT_SOURCE_DIR}/libs/SDL2/include/SDL2
    ${PROJECT_SOURCE_DIR}/libs/SDL2_ttf/include
    ${PROJECT_SOURCE_DIR}/libs/SDL2_ttf/include/SDL2
)

if(WIN32 OR MSYS)
    message(STATUS "Configuring for Windows")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")

    link_directories(
        ${PROJECT_SOURCE_DIR}/libs/SDL2/lib
        ${PROJECT_SOURCE_DIR}/libs/SDL2_ttf/lib
    )

    target_link_libraries(kinematic
        ${PROJECT_SOURCE_DIR}/libs/SDL2/lib/libSDL2.dll.a
        ${PROJECT_SOURCE_DIR}/libs/SDL2_ttf/lib/libSDL2_ttf.dll.a
    )

elseif(APPLE)
    message(STATUS "Configuring for macOS")

    # Use system-installed SDL2 and SDL2_ttf (e.g., via Homebrew)
    find_library(SDL2_LIBRARY SDL2)
    find_library(SDL2_TTF_LIBRARY SDL2_ttf)

    include_directories(/opt/homebrew/include /opt/homebrew/include/SDL2)
    link_directories(/opt/homebrew/lib)

    target_link_libraries(kinematic
        ${SDL2_LIBRARY}
        ${SDL2_TTF_LIBRARY}
    )

endif()