#pragma once

#include <cmath>

namespace kuka_generator
{

    bool float_compare(const float lhs, const float rhs);

    bool float_compare(const float lhs, const float rhs, float epsilon);

    float to_positive_angle(float angle);

}
