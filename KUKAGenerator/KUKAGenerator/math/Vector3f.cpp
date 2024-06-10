#include <Vector3f.h>

#include <math.h>

namespace kuka_generator
{
    Vector3f::Vector3f()
    {
        this->x = 0.0f;
        this->y = 0.0f;
        this->z = 0.0f;
    }

    Vector3f::Vector3f(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void Vector3f::set_values(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double Vector3f::distanceTo(Vector3f& point)
    {
        //calculating distance to another point using pythagoras
        double s = sqrt(pow((double)(x - (double)point.x), 2) + pow((double)(y - (double)point.y), 2) + pow((double)(z - (double)point.z), 2));

        return s;
    }

}
