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
    class Cvelo
    {
        public:
            void getvelocity(std::vector<kuka_generator::DataRow>& data_rows, std::vector<DataRow>::iterator startItr, std::vector<DataRow>::iterator endItr);
            Cvelo(void);
            ~Cvelo(void);

    };
}
