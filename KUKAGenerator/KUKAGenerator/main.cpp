#include <ctime>
#include <iostream>
#include <valarray>

#define _USE_MATH_DEFINES
#include <cmath>

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <stdlib.h>

#include <DataRow.h>
#include <DP.h>
#include <CopyFilterProcessStep.h>
#include <graphics.h>
#include <IProcessStep.h>
#include <LoadInputFileProcessStep.h>
#include <FilterPositionProcessStep.h>
#include <FilterOrientationProcessStep.h>
#include <ProcessContext.h>
#include <userinterface.h>
#include <OutputToKUKASrcFileProcessStep.h>
#include <OutputToFileCallback.h>
#include <velocity.h>

// when the following define is present (line is not removed/commented) then
// the user interface interaction via the command line is executed.
//
// if the next line is removed / commented, then default input and output files
// are defined for testing/debugging purposes. (check all occurences of USE_USER_INPUT
// in this file to see where the defaults are defined)
#define USE_USER_INPUT

using namespace std;

// here, the process context variable is declared.
// This is the variable that is used throughout the entire process.
// It is passed from step to step.
// Each step is allowed to add or remove information to or from the process context.
kuka_generator::ProcessContext process_context;

double to_positive_angle(double angle)
{
    angle = fmod(angle, 360);
    if (angle < 0) angle += 360;
    return angle;
}

int main()
{
    //
    // Create all steps - this is where all instances are created so that they
    // can be used to run the application later
    //

    //
    // Step 1 - read user input
    //
#ifdef USE_USER_INPUT
    kuka_generator::Userinterface userinterface_process_step(process_context);
#endif

    //
    // Step 2 - instantiate "load input file" process step
    // 
    // create the LoadInputFileStep and insert it into the vector
    // pass the process context into the constructor
    kuka_generator::LoadInputFileProcessStep load_input_file_process_step(process_context);

    //
    // Step 3 - instantiate "Apply Filter (Position)" process step
    //

    kuka_generator::FilterPositionProcessStep filter_position_process_step(process_context);

    //
    // Step 4 - instantiate Apply Filter (Orientation) process step
    //

    kuka_generator::FilterOrientationProcessStep filter_orientation_process_step(process_context);

    //
    // Step 5 - instantiate "Douglas Peucker (3D)" process step
    //

    // The Varible DP is given the adress of process_context, the first element, the last element
    // and the tolerance (width of the DP Line) in
    // which the points are allowed to be without creating a new corner point

    kuka_generator::CDP DP;

    //
    // Step 6 - instantiate "Convert rotation matrix to euler angles" process step
    //

    // TODO

    //
    // Step 7 - instantiate "Compute the velocity" process step
    //

    kuka_generator::Cvelo c_velo;

    //
    // Step 8 - Instantiate "Output to in KUKA KRL (.src)" process step
    //

    kuka_generator::OutputToFileCallback output_to_file_callback;
    kuka_generator::OutputToKUKASrcFileProcessStep output_to_KUKA_src_file_process_step(
        process_context, output_to_file_callback);

    //
    // Execute all steps - this is the start of the execution of the process steps
    //

    //
    // step 1 - user input
    //
#ifdef USE_USER_INPUT
    userinterface_process_step.process();
#else
    // this input file will be processed (TODO: step 1 has to produce this information!)
    //process_context.input_file = "resources\\path_01.csv";
    //process_context.input_file = "resources\\path_02.csv";
    process_context.input_file = "resources\\path_03.csv";

    // default output file for testing
    //process_context.output_file = "output\\path_01.src";
    //process_context.output_file = "output\\path_02.src";
    process_context.output_file = "output\\path_03.src";

    process_context.length_filter_orientation = 5;
#endif

    //
    // step 2 - load file into the process context
    //

    int result_load_input_file = load_input_file_process_step.process();
    if (result_load_input_file != kuka_generator::NO_ERROR_RESULT)
    {
        std::cout << "[ERROR] Anwendung wird abgebrochen!" << std::endl;
        std::cout << "[ERROR] Ursache ist, dass das Einlesen der Datendatei " << process_context.input_file << " nicht moeglich war!" << std::endl;

        // return 2 to show that step 2 failed
        return 2;
    }

    //
    // step 3 - filter position
    //

    filter_position_process_step.process();

    //
    // step 4 - filter orientation
    //

    filter_orientation_process_step.process();

    //
    // step 5 - Douglas Peucker (Remove Points)
    //

    std::cout << std::endl << "Step 5 - Douglas Peucker algorithm started" << std::endl;

    double max_distance = process_context.douglas_peucker_max_distance;

    std::vector<kuka_generator::DataRow>::iterator lastItr = std::prev(process_context.data_rows.end());
    DP.DPRecursive(process_context.data_rows, process_context.data_rows.begin(), lastItr, max_distance);

    size_t total_count = process_context.data_rows.size();

    size_t not_deleted_count = std::count_if(std::begin(process_context.data_rows), std::end(process_context.data_rows),
        [](const kuka_generator::DataRow& obj) { return obj.alive; });

    std::cout << "Total: " << total_count << " after Douglas-Peucker: " << not_deleted_count << std::endl;

    //
    // step 6 - Matrix to Euler Angles
    //

    for (kuka_generator::DataRow& data_row : process_context.data_rows)
    {
        data_row.euler_angles.x = 0.0;
        data_row.euler_angles.y = 0.0;
        data_row.euler_angles.z = 0.0;

        if (data_row.orientation_filtered[6] == -1.0f)
        {
            throw 1;
        }
        else if (data_row.orientation_filtered[6] == 1.0f)
        {
            throw 2;
        }
        else
        {
            // R11 R12 R13
            // R21 R22 R23
            // R31 R32 R33

            // [0] [1] [2]
            // [3] [4] [5]
            // [6] [7] [8]

            // B = −asin R31
            data_row.euler_angles.y = -1.0 * asin(data_row.orientation_filtered[6]);
            data_row.euler_angles.y = data_row.euler_angles.y * 180.0f / M_PI;
            data_row.euler_angles.y = to_positive_angle(data_row.euler_angles.y);

            // A = atan2 R21, R11
            data_row.euler_angles.x = 1.0 * atan2(data_row.orientation_filtered[3], data_row.orientation_filtered[0]);
            data_row.euler_angles.x = data_row.euler_angles.x * 180.0f / M_PI;
            data_row.euler_angles.x = to_positive_angle(data_row.euler_angles.x);

            // C = atan2 R32, R33
            data_row.euler_angles.z = 1.0 * atan2(data_row.orientation_filtered[7], data_row.orientation_filtered[8]);
            data_row.euler_angles.z = data_row.euler_angles.z * 180.0f / M_PI;
            data_row.euler_angles.z = to_positive_angle(data_row.euler_angles.z);
        }
    }

    //
    // step 7 - compute speed
    //

    // use the user-defined velocity or compute the actual velocity out of the input
    if (process_context.use_user_defined_velocity)
    {
        // with a velocity of 0.0 the robot arm will not move, so set it to a default value
        double vel = process_context.user_defined_velocity;
        if (float_compare(0.0, process_context.user_defined_velocity))
        {
            vel = 0.5;
        }
        // use the user-defined velocity for all rows
        for (auto& data_row : process_context.data_rows)
        {
            data_row.velocity = vel;
        }
    }
    else
    {
        // compute velocity from timestamp and locations stored in the data
        lastItr = std::prev(process_context.data_rows.end());
        c_velo.getvelocity(process_context.data_rows, process_context.data_rows.begin(), lastItr);
    }

    //
    // step 8 - output to KUKA .src file
    //

    output_to_KUKA_src_file_process_step.process();

    //
    // DEBUG - graphical output - this is an optional output for testing
    //

    // copy data to make the data available in another module of the application
    for (auto& data_row : process_context.data_rows)
    {
        data_rows_for_graphics.push_back(data_row);
    }

    // start the optional graphical output for debugging
    start_graphical_output();

    return 0;
}
