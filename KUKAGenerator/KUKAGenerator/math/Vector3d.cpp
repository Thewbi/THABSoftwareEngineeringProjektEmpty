#include <Vector3d.h>

#include <math.h>

namespace kuka_generator
{
    Vector3d::Vector3d()
    {
        this->x = 0.0;
        this->y = 0.0;
        this->z = 0.0;
    }

    Vector3d::Vector3d(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void Vector3d::set_values(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double Vector3d::distanceTo(Vector3d& point)
    {
        //calculating distance to another point using pythagoras
        double s = sqrt(pow((double)(x - (double)point.x), 2) + pow((double)(y - (double)point.y), 2) + pow((double)(z - (double)point.z), 2));

        return s;
    }

    void Vector3d::normalize()
    {
        double mod = 0.0;

        mod += x * x;
        mod += y * y;
        mod += z * z;

        double mag = std::sqrt(mod);

        x /= mag;
        y /= mag;
        z /= mag;
    }

    Vector3d Vector3d::cross_product(const Vector3d& rhs)
    {
        return Vector3d(
            y * rhs.z - z * rhs.y,
            z * rhs.x - x * rhs.z,
            x * rhs.y - y * rhs.x
        );
    }

}
