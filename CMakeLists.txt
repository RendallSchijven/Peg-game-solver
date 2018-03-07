cmake_minimum_required(VERSION 3.9)
project(peg_game_solver)

set(CMAKE_CXX_STANDARD 11)

add_executable(peg_game_solver pegGame.cpp)
add_executable(8puzzle 8puzzle.cpp)