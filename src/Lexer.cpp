//
// Created by shesh on 5/25/2026.
//

#include "Lexer.h"

#include <format>

#include "LexException.h"


char Lexer::peek() const
{
    if (isEnd())
    {
        return '\0';
    }

    return data[current_index];
}

char Lexer::advance()
{
    if (isEnd())
    {
        return '\0';
    }

    const auto value = peek();

    ++current_index;
    ++col;

    if (value == '\n')
    {
        ++line_number;
        col = 0;
    }

    return value;
}

char Lexer::peekNext() const
{
    if (isNextEnd())
    {
        return '\0';
    }

    return data[current_index + 1];
}

bool Lexer::isEnd() const
{
    return current_index >= data.size();
}

bool Lexer::isNextEnd() const
{
    return current_index + 1 >= data.size();
}


std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> token_list{};

    while (!isEnd())
    {
        switch (auto value = advance())
        {
        case ('{'):
            token_list.emplace_back(TokenType::LBRACE, line_number, col);
            break;
        case ('}'):
            token_list.emplace_back(TokenType::RBRACE, line_number, col);
            break;
        case ('\n'):
        case ('\r'):
        case ('\t'):
        case (' '):
            continue;
        default:
            const std::string error_message{
                std::format("Unexpected character '{}' at line {}, col {}", value, line_number, col - 1)
            };
            throw LexException(error_message);
        }
    }

    if (token_list.empty())
    {
        throw LexException("No Data Provided!");
    }

    token_list.emplace_back(TokenType::END_OF_FILE, line_number, col);

    return token_list;
}
