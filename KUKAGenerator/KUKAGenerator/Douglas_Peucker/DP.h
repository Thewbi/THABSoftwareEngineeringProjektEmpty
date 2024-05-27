// CPoint2D muss noch auf 3D abgeändert werden

#pragma once

#include <vector>
#include <valarray>
#include <list>
#include <iostream>
#include <math.h>
#include<ProcessContext.h>
#include<Line3D.h>


namespace kuka_generator
{
    class CDP
    {
        private:
            double maxDistance;

        public:
            void DPRecursive(ProcessContext* ptr_PContext, std::vector<DataRow>::iterator startItr, std::vector<DataRow>::iterator endItr, double maxDistance);
            CDP(void);
            ~CDP(void);

    };
}
