#pragma once

#include <math.h>
#include <Vector3d.h>

namespace kuka_generator
{
    class CLine3D
    {
    public:
        CLine3D(void);
        CLine3D(kuka_generator::Vector3d& P1, kuka_generator::Vector3d& P2);
        ~CLine3D(void);

        double distanceTo(Vector3d& p);

        kuka_generator::Vector3d p1;
        kuka_generator::Vector3d p2;

    };
}
