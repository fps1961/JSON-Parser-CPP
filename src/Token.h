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

inline std::string tokenTypeToString(const TokenType token_type)
{
    switch (token_type)
    {
    case TokenType::LBRACE:
        return "{";
    case TokenType::RBRACE:
        return "}";
    case TokenType::LBRACKET:
        return "[";
    case TokenType::RBRACKET:
        return "]";
    case TokenType::COLON:
        return ":";
    case TokenType::COMMA:
        return ",";
    case TokenType::STRING:
        return "STRING";
    case TokenType::BOOLEAN:
        return "BOOLEAN";
    case TokenType::END_OF_FILE:
        return "END OF FILE";
    case TokenType::NULL_TYPE:
        return "NULL";
    case TokenType::NUMBER:
        return "NUMBER";
    default:
        return "INVALID";
    }
}


