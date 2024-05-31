#include <Line3D.h>

namespace kuka_generator
{
    CLine3D::CLine3D(void)
    {
    }

    CLine3D::CLine3D(Vector3f P1, Vector3f P2)
    {
        p1 = P1;
        p2 = P2;
    }

    CLine3D::~CLine3D(void)
    {
    }
}
