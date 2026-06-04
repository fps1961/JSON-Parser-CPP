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
    if (peek().type == TokenType::STRING)
    {
        return parseString();
    }
    if (peek().type == TokenType::LBRACE)
    {
        return parseObject();
    }

    return Null{};
}

JsonObject Parser::parseObject()
{
    consume(TokenType::LBRACE);

    JsonObject json_object{};

    while (peek().type != TokenType::RBRACE)
    {
        if (peek().type == TokenType::STRING)
        {
            auto string_value = parseString();

            consume(TokenType::COLON);

            json_object.emplace(string_value, parseValue());

            if (peek().type == TokenType::COMMA)
            {
                consume(TokenType::COMMA);
                if (const auto expected_string = peek(); expected_string.type != TokenType::STRING)
                {
                    throw ParseException(std::format(
                        "Expected String Token Type after Comma but got {} type at line {} col {}!",
                        tokenTypeToString(expected_string.type), expected_string.line_number, expected_string.col));
                }
            }
        }
        else
        {
            throw ParseException(std::format("Expected String Token Type but got {} type at line {} col {}!",
                                             tokenTypeToString(peek().type), peek().line_number, peek().col));
        }
    }

    consume(TokenType::RBRACE);

    return json_object;
}


JsonArray Parser::parseArray()
{
    return {};
}


std::string Parser::parseString()
{
    const auto value = consume(TokenType::STRING).value.value_or("");
    return value;
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

