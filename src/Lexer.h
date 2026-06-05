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

    [[nodiscard]] std::string readString();
    [[nodiscard]] std::string readKeyword(char starting_char);
    [[nodiscard]] std::string readAlpha();


    [[nodiscard]] char peek() const;
    [[nodiscard]] char peekNext() const;
    [[nodiscard]] bool isEnd() const;
    [[nodiscard]] bool isNextEnd() const;

    std::string data;
    int line_number{1};
    int col{0};
    size_t current_index{0};
};
