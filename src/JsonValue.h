//
// Created by shesh on 5/25/2026.
//
#pragma once
#include <map>
#include <string>
#include <variant>
#include <vector>


struct Null
{
};

struct JsonValue;

using JsonObject = std::map<std::string, JsonValue>;
using JsonArray = std::vector<JsonValue>;

struct JsonValue : std::variant<Null, bool, double, std::string, JsonArray, JsonObject>
{
    using variant::variant;
};
