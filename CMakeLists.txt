cmake_minimum_required(VERSION 3.9)
project(BasicIntepreter C)

set(CMAKE_C_STANDARD 11)

add_executable(BasicIntepreter main.c lexer.c interpreter.h interpreter.c arithmetics.c interpreter.h stack.c stack.h)