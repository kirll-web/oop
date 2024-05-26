#pragma once
#include <iostream>
#include <algorithm>

enum class Protocol
{
    HTTP,
    HTTPS
};

std::string StringToLowerCase(std::string const& url);