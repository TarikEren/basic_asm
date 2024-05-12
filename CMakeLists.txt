cmake_minimum_required(VERSION 3.22)
project(basic_asm)

set(CMAKE_CXX_STANDARD 17)

add_executable(basic_asm main.cpp
        headers/Token.h
        headers/Tokenizer.h
        sources/Tokenizer.cpp)
