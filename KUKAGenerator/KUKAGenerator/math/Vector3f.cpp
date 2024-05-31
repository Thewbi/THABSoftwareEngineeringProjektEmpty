#include <Vector3f.h>

#include <math.h>

namespace kuka_generator
{
    double Vector3f::distanceTo(Vector3f& point)
    {
        //calculating distance to another point using pythagoras
        double s = sqrt(pow((double)(x - (double)point.x), 2) + pow((double)(y - (double)point.y), 2) + pow((double)(z - (double)point.z), 2));

        return s;
    }


}
