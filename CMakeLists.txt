cmake_minimum_required(VERSION 3.10)
project(Kinematic)

# Add SDL2 module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Add executable
add_executable(kinematic src/main.c)
target_link_libraries(kinematic ${SDL2_LIBRARIES})

# Set the subsystem to console
if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")
endif()
