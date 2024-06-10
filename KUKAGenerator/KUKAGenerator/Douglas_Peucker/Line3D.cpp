#include <Line3D.h>

namespace kuka_generator
{
    CLine3D::CLine3D(void)
    {
    }

    CLine3D::CLine3D(Vector3f& P1, Vector3f& P2)
    {
        p1 = P1;
        p2 = P2;
    }

    CLine3D::~CLine3D(void)
    {
    }

    double CLine3D::distanceTo(Vector3f& p)
    {
        // see: https://de.serlo.org/mathe/2137/abstand-eines-punktes-zu-einer-geraden-berechnen-analytische-geometrie


        double bx, by, bz, rv_sq, dist;

        // setting the vector for the line
        float rvx = p1.x - p2.x;
        float rvy = p1.y - p2.y;
        float rvz = p1.z - p2.z;

        // calculating the denomintaor of the equasion
        rv_sq = sqrt(((double)rvx * (double)rvx) + ((double)rvy * (double)rvy) + ((double)rvz * (double)rvz));

        // calculation the differnece | first half of the numerator of the equasion
        bx = p.x - (double)p1.x;
        by = p.y - (double)p1.y;
        bz = p.z - (double)p1.z;

        // calculation the cross product
        float cpx = by * rvz - bz * rvy;
        float cpy = bz * rvx - bx * rvz;
        float cpz = bx * rvy - by * rvx;

        // calculating the distance 
        dist = sqrt(cpx * cpx + cpy * cpy + cpz * cpz) / rv_sq;

        return dist;
    }
}
