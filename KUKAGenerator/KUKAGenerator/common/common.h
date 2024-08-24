#pragma once

#include <string>
#include <cctype>
#include <algorithm>

namespace kuka_generator
{
    bool ichar_equals(char a, char b);

    bool equals_ignore_case(const std::string& a, const std::string& b);
}
