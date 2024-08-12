#pragma once

#include <cmath>

namespace kuka_generator
{
    /// <summary>
    /// https://stackoverflow.com/questions/57810925/convenient-vector3f-class
    /// </summary>
    class Vector3d
    {

    public:

        double x{ 0.0 };
        double y{ 0.0 };
        double z{ 0.0 };

        /// <summary>
        /// Default constructor
        ///
        /// Initializes all values x, z and z to zero.
        /// </summary>
        Vector3d();

        /// <summary>
        /// Constructor with coordinates
        /// </summary>
        /// <param name="x">x coordinate</param>
        /// <param name="y">y coordinate</param>
        /// <param name="z">z coordinate</param>
        Vector3d(double x, double y, double z);

        void set_values(double x, double y, double z);

        double distanceTo(Vector3d& point);

        void normalize();

        Vector3d cross_product(const Vector3d& rhs);

        double& operator[](unsigned int i)
        {
            if (i == 0)
            {
                return x;
            }
            if (i == 1)
            {
                return y;
            }
            if (i == 2)
            {
                return z;
            }
        }

        // user-defined copy assignment
        Vector3d& operator=(Vector3d other)
        {
            x = other.x;
            y = other.y;
            z = other.z;

            return *this;
        }

        Vector3d& operator+= (const Vector3d& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;

            return *this;
        }
    };
}
