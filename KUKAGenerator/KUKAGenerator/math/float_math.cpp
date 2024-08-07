#include <float_math.h>

bool float_compare(const float lhs, const float rhs)
{
    return fabs(lhs - rhs) <= 1.0e-05;
}

bool float_compare(const float lhs, const float rhs, float epsilon)
{
    return fabs(lhs - rhs) <= epsilon;
}
