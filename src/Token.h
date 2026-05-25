//
// Created by shesh on 5/25/2026.
//

#pragma once
#include <optional>
#include <string>


enum class TokenType
{
    LBRACE, RBRACE,
    LBRACKET, RBRACKET,
    COLON,
    COMMA,
    STRING,
    NUMBER,
    BOOLEAN,
    NULL_TYPE,
    END_OF_FILE,
    INVALID
};

struct Token
{
    TokenType type{};
    int line_number;
    int col;
    std::optional<std::string> value;
};
