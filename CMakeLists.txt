cmake_minimum_required(VERSION 3.8)
project(calc)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES main.c list.c list.h parser.c parser.h variable.c variable.h executer.c executer.h)
add_executable(calc ${SOURCE_FILES})