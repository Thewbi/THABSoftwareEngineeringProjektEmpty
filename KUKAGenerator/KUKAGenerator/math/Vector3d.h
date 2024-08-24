#pragma once

#include <cmath>
#include <string>

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

        /// <summary>
        /// Set the vector's components.
        /// </summary>
        /// <param name="x">Value for the x component.</param>
        /// <param name="y">Value for the y component.</param>
        /// <param name="z">Value for the z component.</param>
        void set_values(double x, double y, double z);

        /// <summary>
        /// Compute the distance between this vector interpreted 
        /// as a location vector and the the provided vector.
        /// </summary>
        /// <param name="point">The other location vector.</param>
        /// <returns>The distance between the two points.</returns>
        double distanceTo(Vector3d& point);

        /// <summary>
        /// Will keep the orientation of the vector but change the
        /// length of the vector to 1.0
        /// </summary>
        void normalize();

        /// <summary>
        /// Returns a vector that is the result of the cross product
        /// computation between this vector and the other vector
        /// specified by the rhs parameter.
        /// </summary>
        /// <param name="rhs">The other vector to compute the cross product with.</param>
        /// <returns></returns>
        Vector3d cross_product(const Vector3d& rhs);

        /// <summary>
        /// Provides the array indexer operator for the vector data type.
        /// </summary>
        /// <param name="i">index into the array</param>
        /// <returns>returns the x, y or z value stored in the vector given
        /// the indexes 0, 1 and 2 respectively.</returns>
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

        /// <summary>
        /// user-defined copy assignment
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        Vector3d& operator=(Vector3d other)
        {
            x = other.x;
            y = other.y;
            z = other.z;

            return *this;
        }

        /// <summary>
        /// Add-assignment operator
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        Vector3d& operator+= (const Vector3d& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;

            return *this;
        }

        std::string to_string()
        {
            return "[x = " + std::to_string(x) + ", y = " + std::to_string(y) + ", z = " + std::to_string(z) + "]";
        }
    };
}
