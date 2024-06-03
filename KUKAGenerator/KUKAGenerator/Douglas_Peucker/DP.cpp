#include <DP.h>

namespace kuka_generator
{
    CDP::CDP(void)
    {
        std::cout << "Douglas Peucker algorithm started";
    }

    CDP::~CDP(void)
    {

    }

    void CDP::DPRecursive(ProcessContext* ptr_PContext,
        std::vector<DataRow>::iterator startItr, std::vector<DataRow>::iterator endItr, double maxDistance)
    {

        // if the vector has only two points -> return (in this case DP makes no sense)
        if (ptr_PContext->data_rows.size() < 3) return;

        int iter_distance = distance(startItr, endItr);
        //if (iter_distance == 2) return;
        if (iter_distance == 0) return;

        // if the starting point is not alive -> return
        if (startItr->alive == 0) return;
        if (endItr->alive == 0) return;

        // copying the first and the last point into two new variables
        Vector3f pStart; Vector3f pEnd;
        pStart.x = startItr->position_filtered.x;
        pStart.y = startItr->position_filtered.y;
        pStart.z = startItr->position_filtered.z;

        pEnd.x = endItr->position_filtered.x;
        pEnd.y = endItr->position_filtered.y;
        pEnd.z = endItr->position_filtered.z;

        // declaring variables and iterators
        double dist = 0.0;
        double maxDist = 0.0;
        std::vector<DataRow>::iterator maxItr, itr;
        bool value_found = false;

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
            dist = line.distanceTo(itr->position_filtered);

            // check for NAN (not a number)
            // https://stackoverflow.com/questions/570669/checking-if-a-double-or-float-is-nan-in-c
            //
            // According to the IEEE standard, NaN values have the odd property that comparisons involving them are always false.
            // That is, for a float f, f != f will be true only if f is NaN.

            if (dist != dist)
            {
                std::cout << "NAN" << std::endl;
            }

            // saving the information of the point with the greatest distance
            if (dist > maxDist)
            {
                maxDist = dist;
                maxItr = itr;
                value_found = true;
            }
        }

        // if the points are in the set tolerance they get deleted
        // if not the points will exist further
        if (maxDist <= maxDistance)
        {
            for (itr = ++startItr; itr != endItr; itr++)
            {
                itr->alive = 0;
            }

        }

        if (value_found)
        {
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

}
