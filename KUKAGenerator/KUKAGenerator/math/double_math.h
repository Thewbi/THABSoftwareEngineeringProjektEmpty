#pragma once

#include <cmath>

namespace kuka_generator
{
    bool double_compare(const double lhs, const double rhs);

    bool double_compare(const double lhs, const double rhs, double epsilon);

    double to_positive_angle(double angle);
}
