//
// Created by shesh on 5/25/2026.
//

#include "Parser.h"

#include <format>

#include "ParseException.h"


JsonValue Parser::parse()
{
    auto json_value = parseValue();
    consume(TokenType::END_OF_FILE);
    return json_value;
}

JsonValue Parser::parseValue()
{
    if (peek().type != TokenType::LBRACE)
    {
        throw ParseException(std::format("Unexpected token '{}' at line {}, col {} - expected a value\n",
                                         tokenTypeToString(peek().type), peek().line_number, peek().col));
    }

    return parseObject();
}

JsonObject Parser::parseObject()
{
    consume(TokenType::LBRACE);
    consume(TokenType::RBRACE);
    return {};
}


JsonArray Parser::parseArray()
{
    return {};
}


std::string Parser::parseString()
{
    return {};
}

Token Parser::peek() const
{
    if (current_index >= token_list.size())
    {
        throw ParseException("Unexpected end of input\n");
    }

    return token_list[current_index];
}


Token Parser::consume(const TokenType expected_token_type)
{
    if (current_index >= token_list.size())
    {
        throw ParseException("Unexpected end of input");
    }

    auto token = token_list[current_index];

    if (token.type != expected_token_type)
    {
        throw ParseException(std::format("Expected '{}' token type but got '{}' at line {}, col {}\n",
                                         tokenTypeToString(expected_token_type), tokenTypeToString(token.type),
                                         token.line_number, token.col));
    }
    ++current_index;
    return token;
}

