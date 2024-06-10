#pragma once

#include <iostream>
#include <Line3D.h>
#include <list>
#include <math.h>
#include <ProcessContext.h>
#include <valarray>
#include <vector>

namespace kuka_generator
{
    class CDP
    {
    private:
        double maxDistance;

    public:
        void DPRecursive(std::vector<kuka_generator::DataRow>& data_rows, std::vector<DataRow>::iterator startItr, std::vector<DataRow>::iterator endItr, double maxDistance);
        CDP(void);
        ~CDP(void);

    };
}
