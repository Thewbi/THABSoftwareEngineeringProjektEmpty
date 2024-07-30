#include <velocity.h>

namespace kuka_generator
{
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

        do
        {
            // finding the first point wich is alive and has no velocity
            for (itr = startItr; itr == endItr; itr++)
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

            //finding the nex point wich is alive
            for (itr; (itr->alive == true) || itr == endItr; itr++)
            {
                if (itr->alive == false)
                {
                    continue;
                }

                pEnd.x = endItr->position_filtered.x;
                pEnd.y = endItr->position_filtered.y;
                pEnd.z = endItr->position_filtered.z;
                break;
            }

            double distx = pEnd.x - pStart.x;
            double disty = pEnd.y - pStart.y;
            double distz = pEnd.z - pStart.z;

            double distlength = sqrt((distx * distx) + (disty * disty) + (distz + distz));
            double calcvelo = distlength / ((itr->timestamp) - starttime);

            firstpoint->velocity = calcvelo;

        } while (itr != endItr);
    }





}
