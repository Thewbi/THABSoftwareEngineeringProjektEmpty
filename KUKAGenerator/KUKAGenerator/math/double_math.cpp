#include <double_math.h>

bool kuka_generator::double_compare(const double lhs, const double rhs)
{
    return fabs(lhs - rhs) <= 1.0e-05;
}

bool kuka_generator::double_compare(const double lhs, const double rhs, double epsilon)
{
    return fabs(lhs - rhs) <= epsilon;
}
