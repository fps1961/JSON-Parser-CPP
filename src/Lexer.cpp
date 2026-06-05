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
        const auto line_number = this->line_number;
        const auto col = this->col;
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
        case ('"'):
            token_list.emplace_back(TokenType::STRING, line_number, col, readString());
            break;
        case (':'):
            token_list.emplace_back(TokenType::COLON, line_number, col);
            break;
        case (','):
            token_list.emplace_back(TokenType::COMMA, line_number, col);
            break;
        case ('t'):
        case ('f'):
            token_list.emplace_back(TokenType::BOOLEAN, line_number, col, readKeyword(value));
            break;
        case ('n'):
            token_list.emplace_back(TokenType::NULL_TYPE, line_number, col, readKeyword(value));
            break;
        default:
            const std::string error_message{
                std::format("Unexpected character '{}' at line {}, col {}\n", value, line_number, col)
            };
            throw LexException(error_message);
        }
    }

    if (token_list.empty())
    {
        throw LexException("No Data Provided!\n");
    }

    token_list.emplace_back(TokenType::END_OF_FILE, line_number, col);

    return token_list;
}

std::string Lexer::readString()
{
    std::string value{};

    while (!isEnd() && peek() != '"')
    {
        if (const auto curr_char = advance(); curr_char == '\\')
        {
            switch (const auto escape_char = advance())
            {
            case ('n'):
                value += '\n';
                break;
            case ('t'):
                value += '\t';
                break;
            case ('r'):
                value += '\r';
                break;
            case ('b'):
                value += '\b';
                break;
            case ('f'):
                value += '\f';
                break;
            case ('"'):
                value += '\"';
                break;
            case ('\\'):
                value += '\\';
                break;
            case ('/'):
                value += '/';
                break;
            default:
                throw LexException(std::format("Unknown Escape Sequence Encountered:{}", escape_char));
            }
        }
        else
        {
            value += curr_char;
        }
    }

    if (isEnd())
    {
        throw LexException("Expected '\"' when reading string");
    }

    advance();

    return value;
}

std::string Lexer::readKeyword(const char starting_char)
{
    std::string keyword(1, starting_char);

    keyword += readAlpha();


    if (keyword == "true" || keyword == "false" || keyword == "null")
    {
        return keyword;
    }

    throw LexException(std::format("Unexpected value {} in json at line {}, col {}", keyword, line_number, col));
}

std::string Lexer::readAlpha()
{
    std::string value{};

    while (isalpha(peek()))
    {
        value += advance();
    }

    return value;
}



