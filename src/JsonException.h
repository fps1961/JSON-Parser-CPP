//
// Created by shesh on 5/25/2026.
//

#pragma once
#include <stdexcept>

class JsonException : public std::runtime_error
{
    using runtime_error::runtime_error;
};
