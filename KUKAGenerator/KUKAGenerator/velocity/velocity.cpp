#include <velocity.h>

namespace kuka_generator
{

    Cvelo::Cvelo()
    {

    }

    Cvelo::~Cvelo()
    {

    }

    void Cvelo::getvelocity(std::vector<kuka_generator::DataRow>& data_rows, std::vector<DataRow>::iterator startItr, std::vector<DataRow>::iterator endItr)
    {
        // if there is noc distance between starting point and end point -> return
        if (distance(startItr, endItr) == 0)
        {
            return;
        }

        std::vector<DataRow>::iterator itr, firstpoint;
        Vector3f pStart;
        Vector3f pEnd;
        long starttime = 0;

        itr = startItr;

        do
        {
            // finding the first point which is alive and has no velocity
            for (; itr != endItr; itr++)
            {
                if ((itr->alive == false) || (itr->velocity != 0.0))
                {
                    continue;
                }

                firstpoint = itr;
                pStart.x = itr->position_filtered.x;
                pStart.y = itr->position_filtered.y;
                pStart.z = itr->position_filtered.z;
                starttime = itr->timestamp;

                break;
            }

            itr++;

            // finding the next point which is alive
            for (; itr != endItr; itr++)
            {
                if (itr->alive == false)
                {
                    continue;
                }

                pEnd.x = itr->position_filtered.x;
                pEnd.y = itr->position_filtered.y;
                pEnd.z = itr->position_filtered.z;
                break;
            }

            if (itr == endItr)
            {
                pEnd.x = itr->position_filtered.x;
                pEnd.y = itr->position_filtered.y;
                pEnd.z = itr->position_filtered.z;
            }

            double distx = pEnd.x - pStart.x;
            double disty = pEnd.y - pStart.y;
            double distz = pEnd.z - pStart.z;

            double sum_of_squares = (distx * distx) + (disty * disty) + (distz + distz);
            double distlength = sqrt(abs(sum_of_squares));

            double divisor = ((itr->timestamp) - starttime);
            if (kuka_generator::double_compare(0.0, divisor))
            {
                firstpoint->velocity = 0.5;
            }
            else
            {
                double calcvelo = distlength / divisor;
                firstpoint->velocity = calcvelo;
            }

        } while (itr != endItr);

    }

}
