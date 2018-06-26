cmake_minimum_required(VERSION 3.9)
project(BasicIntepreter C)

set(CMAKE_C_STANDARD 11)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

add_executable(BasicIntepreter main.c lexer.c executer.c arithmetics.c stack.c stack.h lexer.h arithmetics.h executer.h token.h errors.c errors.h instructions.h interpreter.c interpreter.h interpreter.h arithmetics.h)