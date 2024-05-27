#include <DP.h>

namespace kuka_generator
{
    
    
    void CDP::DPRecursive(ProcessContext* ptr_PContext, std::vector<DataRow>::iterator startItr, std::vector<DataRow>::iterator endItr, double maxDistance)
    {
        
        // if the vector has only two points -> return (in this case DP makes no sense)
        if (ptr_PContext->data_rows.size() < 3) return;
        if (distance(startItr, endItr) == 2) return;

        Vector3f pStart; Vector3f pEnd;
        pStart.x = startItr->position_filtered.x;
        pStart.y= startItr->position_filtered.y;

        //pEnd.x=segment.back().x; pEnd.y = segment.back().y;
        pEnd.x = endItr->position_filtered.x;
        pEnd.y = endItr->position_filtered.y;

        double dist = 0.0, maxDist = 0.0;
        std::vector<DataRow>::iterator maxItr, itr;

        for (itr = startItr; itr != endItr; itr++)
        {
            CLine3D line = CLine3D(pStart, pEnd);
            // calc distance
            dist = itr->position.distanceTo(line);
            //dist=calcDist(pStart.getX(), pStart.getY(), pEnd.getX(), pEnd.getY(), itr->getX(), itr->getY());
            if (dist > maxDist) {
                maxDist = dist;
                maxItr = itr;
            }
        }

        if (maxDist <= maxDistance) {

            (++startItr)->alive=0;
            //segment.erase((++startItr), endItr);
            //for(itr = (++startItr); itr != --(endItr);)
            //{
            //	// erase elements:
            //	itr = segment.erase(itr);
            //}
            return;
        }

        DPRecursive(ptr_PContext, startItr, maxItr, maxDistance);
        DPRecursive(ptr_PContext, maxItr, endItr, maxDistance);
    }

}
