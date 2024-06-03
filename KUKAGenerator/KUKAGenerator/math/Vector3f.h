#pragma once

namespace kuka_generator
{
    /// <summary>
    /// https://stackoverflow.com/questions/57810925/convenient-vector3f-class
    /// </summary>
    class Vector3f
    {

    public:

        float x{ 0.0f };
        float y{ 0.0f };
        float z{ 0.0f };

        /// <summary>
        /// Default constructor
        ///
        /// Initializes all values x, z and z to zero.
        /// </summary>
        Vector3f();

        /// <summary>
        /// Constructor with coordinates
        /// </summary>
        /// <param name="x">x coordinate</param>
        /// <param name="y">y coordinate</param>
        /// <param name="z">z coordinate</param>
        Vector3f(float x, float y, float z);

        double distanceTo(Vector3f& point);

        float& operator[](unsigned int i)
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
        Vector3f& operator=(Vector3f other)
        {
            x = other.x;
            y = other.y;
            z = other.z;

            return *this;
        }
    };
}
