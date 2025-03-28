cmake_minimum_required(VERSION 3.10)
project(Kinematic)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)

if(APPLE)
    include(FindPkgConfig)
    pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
    
    if(NOT SDL2_TTF_INCLUDE_DIRS)
        execute_process(
            COMMAND brew --prefix sdl2_ttf
            OUTPUT_VARIABLE BREW_SDL2_TTF_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        set(SDL2_TTF_INCLUDE_DIRS "${BREW_SDL2_TTF_PREFIX}/include")
        set(SDL2_TTF_LIBRARIES "${BREW_SDL2_TTF_PREFIX}/lib/libSDL2_ttf.dylib")
    endif()
else()
    find_package(SDL2_ttf REQUIRED)
endif()

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

add_executable(kinematic src/main.c)
target_link_libraries(kinematic ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")
endif()