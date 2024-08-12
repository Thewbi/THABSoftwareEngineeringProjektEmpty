#include <DP.h>

namespace kuka_generator
{
    CDP::CDP(void)
    {
        //std::cout << "Douglas Peucker algorithm started";
    }

    CDP::~CDP(void)
    {

    }

    /// <summary>
    /// Implementation:
    /// First, a line is created from the first to the last point. This line is
    /// used to compute the distance of points to the line.
    /// 
    /// In an initial step, the distances of all points to the line are computed.
    /// In this first step, the maxDistance is not even used and makes no difference on the first step.
    ///
    /// In a second step, if the point furthest away is still within the max distance, then
    /// the entire set of points is erased and only start and end are kept alive. There is
    /// no further recursion performed in this case!
    ///
    /// If the point that is furthest away is outside the max distance, then recursion is
    /// necessary. The data is broken up into two sets. Set A is from start to the furthest point.
    /// Set B is from the furthest point to the end.
    /// 
    /// </summary>
    /// <param name="data_rows"></param>
    /// <param name="startItr"></param>
    /// <param name="endItr"></param>
    /// <param name="maxDistance"></param>
    void CDP::DPRecursive(std::vector<kuka_generator::DataRow>& data_rows,
        std::vector<DataRow>::iterator startItr, std::vector<DataRow>::iterator endItr, double maxDistance)
    {
        // if the vector has only two points -> return (in this case DP makes no sense)
        if (data_rows.size() < 3)
        {
            return;
        }

        if (distance(startItr, endItr) == 0)
        {
            return;
        }

        // if the starting point is not alive -> return
        if ((startItr->alive == false) || (endItr->alive == false))
        {
            return;
        }

        // copying the first and the last point into two new variables
        Vector3d pStart;
        pStart.x = startItr->position_filtered.x;
        pStart.y = startItr->position_filtered.y;
        pStart.z = startItr->position_filtered.z;

        Vector3d pEnd;
        pEnd.x = endItr->position_filtered.x;
        pEnd.y = endItr->position_filtered.y;
        pEnd.z = endItr->position_filtered.z;

        // declaring variables and iterators
        double dist = 0.0;
        double maxDist = 0.0;
        std::vector<DataRow>::iterator maxItr, itr;
        bool maxdistance_point_found = false;

        // setting a line
        // e.g. the first line is set between the first and the last point
        // in the next repitition of the loop the line is set between the first point
        // and the point with the greatest distance between itself and the line in the loop before
        // see Douglas Peucker algorithm 
        CLine3D line = CLine3D(pStart, pEnd);

        for (itr = startItr; itr != endItr; itr++)
        {
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
                maxdistance_point_found = true;
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

            // no need to recurse further, all points have been removed already
            maxdistance_point_found = false;
        }

        // if the max distance point is outside the allowed distance, recurse
        if (maxdistance_point_found)
        {
            // the function will call itself with new parameters
            // the new line that is going to be set will be between the first and the point with the greatest distance
            // this will be done until all points that are in the tolerance will be deleted
            // the target is to delete all unnecessary points 
            DPRecursive(data_rows, startItr, maxItr, maxDistance);

            // the function will call itself again to delete the points in the second half
            // (from the point with the gratest distance and the last one) 
            DPRecursive(data_rows, maxItr, endItr, maxDistance);
        }

    }

}
