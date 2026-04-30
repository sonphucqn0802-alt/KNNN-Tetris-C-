cmake_minimum_required(VERSION 3.16)

project(TetrisCpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(tetris
    src/AudioManager.cpp
    src/Board.cpp
    src/GameLoop.cpp
    src/InputHandler.cpp
    src/Renderer.cpp
    src/SaveManager.cpp
    src/ScoreManager.cpp
    src/Tetromino.cpp
    src/main.cpp
)

target_include_directories(tetris PRIVATE include)

if (MSVC)
    target_compile_options(tetris PRIVATE /W4)
else()
    target_compile_options(tetris PRIVATE -Wall -Wextra -pedantic)
endif()
