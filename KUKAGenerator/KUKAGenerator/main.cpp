#include <ctime>
#include <iostream>
#include <valarray>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>

#include <stdlib.h>

#include "DataRow.h"
#include "DP.h"
#include <CopyFilterProcessStep.h>
#include <ExampleProcessStep.h>
#include <graphics.h>
#include <IProcessStep.h>
#include <LoadInputFileProcessStep.h>
#include <ProcessContext.h>
#include <userinterface.h>
#include <OutputToKUKASrcFileProcessStep.h>


#define USE_USER_INPUT


using namespace std;

// here, the process context variable is declared.
// This is the variable that is used throughout the entire process.
// It is passed from step to step.
// Each step is allowed to add or remove information to or from the process context.
kuka_generator::ProcessContext process_context;



int main()
{
    //
    // Create all steps
    //

    //// Step 0 - example step
    ////
    //// this step does nothing really
    //kuka_generator::ExampleProcessStep example_process_step(process_context);

    // Step 1 - read user input
    //
#ifdef USE_USER_INPUT
    kuka_generator::Userinterface userinterface_process_step(process_context);
#endif

    // Step 2 - load input file
    // 
    // create the LoadInputFileStep and insert it into the vector
    // pass the process context into the constructor
    kuka_generator::LoadInputFileProcessStep load_input_file_process_step(process_context);

    // Step 3 - Apply Filter (Position)
    //

    // Step 4 - Apply Filter (Orientation)
    //

    // TODO: replace this implementation by a real implementation
    kuka_generator::CopyFilterProcessStep copy_filter_process_step(process_context);

    // Step 5 - Douglas Peucker (3D)
    //

    // The Varible DP is given the adress of process_context, the first element, the last element
    // and the tolerance (width of the DP Line) in
    // which the points are allowed to be without creating a new corner point

    kuka_generator::CDP DP;

    // Step 6 - Umrechnung Orientierungsmatrix in Euler Winkel
    //

    // Step 7 - Berechnung der Geschwindigkeit
    //

    // Step 8 - Ausgabe in KUKA KRL (.src)
    //

    kuka_generator::OutputToKUKASrcFileProcessStep output_to_KUKA_src_file_process_step(process_context);

    //
    // Execute all steps
    //

    // step 0 - example
    //

//    example_process_step.process();

    // step 1 - user input
    //
#ifdef USE_USER_INPUT
    userinterface_process_step.process();
#else
    // this input file will be processed (TODO: step 1 has to produce this information!)
    //process_context.input_file = "resources\\path_01.csv";
    //process_context.input_file = "resources\\path_02.csv";
    process_context.input_file = "resources\\path_03.csv";

    process_context.output_file = "output\\path_03.src";
#endif

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

    // step 3 - filter position
    //

    // TODO

    // step 4 - filter orientation
    //

    // TODO

    // TODO: replace this implementation by a real implementation
    // 
    // this is needed to have any usable data in the filtered position data.
    // Otherwise the filtered data is just 0 and the doublas peucker will not work correctly
    copy_filter_process_step.process();

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

    // step 6 - Matrix to Euler Angles
    //

    // TODO

    // step 7 - compute speed
    //

    // TODO

    // step 8 - output to KUKA .src file
    //

    output_to_KUKA_src_file_process_step.process();

    //
    // DEBUG - graphical output
    //

    for (auto& data_row : process_context.data_rows)
    {
        data_rows_for_graphics.push_back(data_row);
    }
    start_graphical_output();

    return 0;
}
