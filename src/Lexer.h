//
// Created by shesh on 5/25/2026.
//

#pragma once
#include <utility>
#include <vector>

#include "Token.h"


class Lexer
{
public:
    explicit Lexer(std::string data) : data(std::move(data))
    {
    };

    std::vector<Token> tokenize();

private:
    char advance();

    [[nodiscard]] char peek() const;
    [[nodiscard]] char peekNext() const;
    [[nodiscard]] bool isEnd() const;
    [[nodiscard]] bool isNextEnd() const;

    std::string data;
    int line_number{1};
    int col{0};
    int current_index{0};
};
