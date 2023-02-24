cmake_minimum_required(VERSION 3.23)
project(chess_engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(chess_engine main.cpp Board.cpp Board.h defs.h bitops.h)
