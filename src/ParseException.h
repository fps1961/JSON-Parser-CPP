//
// Created by shesh on 5/25/2026.
//

#pragma once
#include "JsonException.h"

class ParseException : public JsonException
{
    using JsonException::JsonException;
};
