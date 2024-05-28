#include <DP.h>

namespace kuka_generator
{
    void CDP::CDP(void)
    {
        std::cout << "Douglas Peucker algorithm started";
    }

    void CDP::~CDP(void)
    {

    }
    
    void CDP::DPRecursive(ProcessContext* ptr_PContext, std::vector<DataRow>::iterator startItr, std::vector<DataRow>::iterator endItr, double maxDistance)
    {
        
        // if the vector has only two points -> return (in this case DP makes no sense)
        if (ptr_PContext->data_rows.size() < 3) return;
        if (distance(startItr, endItr) == 2) return;

        // copying the first and the last point into two new variables
        Vector3f pStart; Vector3f pEnd;
        pStart.x = startItr->position_filtered.x;
        pStart.y = startItr->position_filtered.y;
        pStart.z = startItr->position_filtered.z;

        pEnd.x = endItr->position_filtered.x;
        pEnd.y = endItr->position_filtered.y;
        pEnd.z = endItr->position_filtered.z;

        // declaring variables and iterators
        double dist = 0.0, maxDist = 0.0;
        std::vector<DataRow>::iterator maxItr, itr;

        for (itr = startItr; itr != endItr; itr++)
        {
            // setting a line
            // e.g. the first line is set between the first and the last point
            // in the next repitition of the loop the line is set between the first point
            // and the point with the greatest distance between itself and the line in the loop before
            // see Douglas Peucker algorithm 
            CLine3D line = CLine3D(pStart, pEnd);

            // calculate the distance from each point to the line to find out which point is the one
            // with the greatest distance
            dist = itr->position.distanceTo(line);

            // saving the information of the point with the greatest distance
            if (dist > maxDist) {
                maxDist = dist;
                maxItr = itr;
            }
        }

        // if the point with the greatest distance is in the set tolerance it gets deleted
        // if not the point will exist further
        if (maxDist <= maxDistance) {

            (++startItr)->alive=0;
          
            return;
        }

        // the function will call itself with new parameters
        // the new line that is going to be set will be between the first and the point with the greatest distance
        // this will be done until all points that are in the tolerance will be deleted
        // the target is to delete all unnecessary points 
        DPRecursive(ptr_PContext, startItr, maxItr, maxDistance);

        // the function will call itself again to delete the points in the second half
        // (from the point with the gratest distance and the last one) 
        DPRecursive(ptr_PContext, maxItr, endItr, maxDistance);
    }

}
