#include <Vector3f.h>
#include <math.h>

#pragma once
namespace kuka_generator
{
    class CLine3D
    {
    public:
        CLine3D(void);
        CLine3D(Vector3f P1, Vector3f P2);
        ~CLine3D(void);

        Vector3f p1;
        Vector3f p2;

    };
}
