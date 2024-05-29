#include <Vector3f.h>

#include <math.h>

namespace kuka_generator
{
    double Vector3f::distanceTo(Vector3f point)
    {
        //calculating distance to another point using pythagoras
        double s = sqrt(pow((double)(x - (double)point.x), 2) + pow((double)(y - (double)point.y), 2) + pow((double)(z - (double)point.z), 2));

        return s;
    }

    double Vector3f::distanceTo(CLine3D line)
    {
        // see: https://de.serlo.org/mathe/2137/abstand-eines-punktes-zu-einer-geraden-berechnen-analytische-geometrie


        double bx, by, bz, rv_sq, dist;

        // setting the vector for the line
        float rvx = line.p1.x - line.p2.x;
        float rvy = line.p1.y - line.p2.y;
        float rvz = line.p1.z - line.p2.z;

        // calculating the denomintaor of the equasion
        rv_sq = sqrt(((double)rvx * (double)rvx) + ((double)rvy * (double)rvy) + ((double)rvz * (double)rvz));

        // calculation the differnece | first half of the numerator of the equasion
        bx = x - (double)line.p1.x;
        by = y - (double)line.p1.y;
        bz = z - (double)line.p1.z;

        // calculation the cross product
        float cpx = by * rvz - bz * rvy;
        float cpy = bz * rvx - bx * rvz;
        float cpz = bx * rvy - by * rvx;
        
        // calculating the distance 
        dist = sqrt(cpx*cpx + cpy*cpy + cpz*cpz) / rv_sq;

        return dist;
    }
}
