cmake_minimum_required(VERSION 3.16)
project(sandbox C)

set(CMAKE_C_STANDARD 11)

add_executable(copyFilePosix copyFilePosix.c)
add_executable(rough rough.c)
add_executable(fork_learn processes/fork_learn.c)
add_executable(shared_memory_producer processes/shared_memory_producer.c)
add_executable(c_shared_consumer processes/c_shared_consumer.c)
add_executable(fork_party processes/fork_party.c)
add_executable(pipe_ipc processes/pipe_ipc.c)