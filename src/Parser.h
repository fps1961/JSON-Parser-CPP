//
// Created by shesh on 5/25/2026.
//

#pragma once
#include <vector>

#include "JsonValue.h"
#include "Token.h"


class Parser
{
public:
    explicit Parser(const std::vector<Token>& token_list) : token_list(token_list)
    {
    };

    JsonValue parse();

private:
    std::vector<Token> token_list{};
    size_t current_index{0};

    JsonValue parseValue();
    JsonObject parseObject();
    JsonArray parseArray();
    std::string parseString();

    Token peek() const;
    Token consume(TokenType expected_token_type);
};
