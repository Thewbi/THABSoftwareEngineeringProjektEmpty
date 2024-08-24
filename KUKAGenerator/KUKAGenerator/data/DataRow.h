#pragma once

#include <string>
#include <vector>

#include <Matrix3x3f.h>
#include <Vector3f.h>
#include <Vector3d.h>

namespace kuka_generator
{
    class DataRow
    {

    public:

        int index{ -1 };

        // timestamp, read from the input file
        long timestamp{ 0 };

        // stores the unfiltered position (defined by either the user or read from the input file)
        Vector3d position;

        // keep the original data intact e.g. for applying filters to the original data.
        // Therefore filtered data is copied into this member variable.
        Vector3d position_filtered;

        // stores the unfiltered orientation (defined by either the user or read from the input file)
        //Matrix3x3f orientation;
        Matrix3x3d orientation;

        // keep the original data intact e.g. for applying filters to the original data.
        // Therefore filtered data is copied into this member variable.
        //Matrix3x3f orientation_filtered;
        Matrix3x3d orientation_filtered;

        // velocity at that point (either defined by the user or computed dynamically given the timestamp and the distance)
        double velocity{ 0.0 };

        // if the Douglas-Peucker algorithm decides to delete a point, the point is not actually deleted.
        // The point is kept but it's alive flag is set to false
        bool alive{ true };

        // resulting euler angles as mandated by the KAKA IRL output format
        Vector3d euler_angles;

    public:

        std::string to_string()
        {
            return "index: " + std::to_string(index)
                + " timestamp: " + std::to_string(timestamp)
                + " position: " + position.to_string()
                + " position_filtered: " + position_filtered.to_string()
                + " orientation: " + orientation.to_string()
                + " orientation_filtered: " + orientation_filtered.to_string()
                + " velocity: " + std::to_string(velocity)
                + " alive: " + std::to_string(alive)
                + " euler_angles: " + euler_angles.to_string()
                ;
        }
    };
}
