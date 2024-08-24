#include <common.h>

bool kuka_generator::ichar_equals(char a, char b)
{
    return std::tolower(static_cast<unsigned char>(a)) ==
        std::tolower(static_cast<unsigned char>(b));
}

bool kuka_generator::equals_ignore_case(const std::string& a, const std::string& b)
{
    return std::equal(a.begin(), a.end(), b.begin(), b.end(), ichar_equals);
}
