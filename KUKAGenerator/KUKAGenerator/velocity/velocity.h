#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <valarray>

#include <Line3D.h>
#include <math.h>
#include <ProcessContext.h>
#include <double_math.h>

namespace kuka_generator
{

    class Cvelo
    {
    private:
        const double default_velocity = 0.2;
    public:
        void getvelocity(std::vector<kuka_generator::DataRow>& data_rows, std::vector<DataRow>::iterator startItr, std::vector<DataRow>::iterator endItr);
        Cvelo(void);
        ~Cvelo(void);

    };
}
