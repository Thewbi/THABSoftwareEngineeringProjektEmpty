#include <math.h>
#include <Vector3f.h>

#pragma once
namespace kuka_generator
{
    class CLine3D
    {
    public:
        CLine3D(void);
        CLine3D(kuka_generator::Vector3f& P1, kuka_generator::Vector3f& P2);
        ~CLine3D(void);

        double distanceTo(Vector3f& p);

        kuka_generator::Vector3f p1;
        kuka_generator::Vector3f p2;

    };
}
