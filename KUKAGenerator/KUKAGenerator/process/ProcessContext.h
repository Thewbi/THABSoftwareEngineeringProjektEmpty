#pragma once

#include <string>
#include <vector>

#include <DataRow.h>
#include <Matrix3x3f.h>

namespace kuka_generator
{
    class ProcessContext
    {

    public:

        // the user defined input file
        std::string input_file{ "" };

        // the user defined output file
        std::string output_file{ "" };

        // true = the user has supplied a orientation to use for all parts of the trajectory (the orientation from the input file is ignored)
        // false = the orientations should be read from the input file
        bool use_user_defined_orientation{ false };

        // this is the user defined orientation (this field contains no valid data if the orientation is read from the input file)
        Matrix3x3f user_defined_orientation;

        // true = the user has supplied a velocity to use for all parts of the trajectory (the velocity from the input file is ignored)
        // false = the velocities should be read from the input file
        bool use_user_defined_velocity{ false };

        // this is the user defined velocity (this field contains no valid data if the velocity is read from the input file)
        double user_defined_velocity{ 0.0 };

        // amount of elements to compute the orientation filter accross
        int length_filter_orientation{ 1 };

        // amount of elements to compute the position filter accross
        int length_filter_position{ 1 };

        // distance for douglas peucker
        //
        //constexpr double max_distance = 99999.0;
        //constexpr double max_distance = 25.0; // good compression for testset 1
        //constexpr double max_distance = 5.0; // good compression for testset 2 and testset 3
        //constexpr double max_distance = 0.5;
        //constexpr double max_distance = 0.001;
        double douglas_peucker_max_distance = 5.0;

        // all parts (Stützstellen) of the trajectory
        std::vector<DataRow> data_rows;
    };
}
