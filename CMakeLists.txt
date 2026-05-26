#[[
Cau hinh cach bien dich va lien ket cac thanh phan cua du an Tetris C++.
]]

cmake_minimum_required(VERSION 3.16)

project(KNNN_Tetris_Cpp
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(tetris
    src/AudioManager.cpp
    src/Board.cpp
    src/GameLoop.cpp
    src/InputHandler.cpp
    src/main.cpp
    src/Renderer.cpp
    src/SaveManager.cpp
    src/ScoreManager.cpp
    src/Tetromino.cpp
)

target_include_directories(tetris PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(tetris PRIVATE /W4)
else()
    target_compile_options(tetris PRIVATE -Wall -Wextra -pedantic)
endif()
