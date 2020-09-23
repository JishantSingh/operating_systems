cmake_minimum_required(VERSION 3.17)
project(sandbox C)

set(CMAKE_C_STANDARD 11)

add_executable(sandbox copyFilePosix.c rough.c processes/fork_learn.c)