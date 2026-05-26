cmake_minimum_required(VERSION 3.28.3)
project(JSON_Parser_CPP)

set(CMAKE_CXX_STANDARD 20)

add_executable(JSON_Parser_CPP src/main.cpp
        src/Token.h
        src/JsonValue.h
        src/Lexer.cpp
        src/Lexer.h
        src/Parser.cpp
        src/Parser.h
        src/JsonException.h
        src/LexException.h
        src/ParseException.h)
