cmake_minimum_required(VERSION 3.16)
project(Tetris VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GAME_EXECUTABLE Tetris)

add_subdirectory("dependencies")

include_directories("${CMAKE_SOURCE_DIR}/src")
include_directories("${CMAKE_SOURCE_DIR}/dependencies/stb/include")
file(GLOB_RECURSE GAME_SOURCE_FILES "src/*.cpp" "src/*.h")

add_executable(${GAME_EXECUTABLE} ${GAME_SOURCE_FILES})
target_precompile_headers(${GAME_EXECUTABLE} PRIVATE src/pch.h)
target_link_libraries(${GAME_EXECUTABLE} PRIVATE SDL2 glad glm spdlog freetype)
