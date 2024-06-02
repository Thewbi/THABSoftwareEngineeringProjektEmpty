#include <ctime>
#include <iostream>
#include <valarray>

#include <ExampleProcessStep.h>
#include <IProcessStep.h>
#include <LoadInputFileProcessStep.h>
#include <ProcessContext.h>
#include "DP.h"
#include "BmpHandler.h"
#include "DataRow.h"


using namespace std;

int main()
{
    // here, the process context variable is declared.
    // This is the variable that is used throughout the entire process.
    // It is passed from step to step. Each step is allowed to add or remove information from the context.
    kuka_generator::ProcessContext process_context;

    // create a vector into which all steps are inserted,
    // so all steps can be executed in the exact order using a for-loop
    std::vector<kuka_generator::IProcessStep*> steps;

    //
    // Create all steps
    //

    // example
    kuka_generator::ExampleProcessStep example_process_step(process_context);
    steps.push_back(&example_process_step);

    // Step 1 - read user input
    //
    // this input file will be processed (TODO: step 1 has to produce this information!)
    process_context.input_file = "resources\\path_01.csv";

    // Step 2 - load input file
    // 
    // create the LoadInputFileStep and insert it into the vector
    // pass the process context into the constructor
    kuka_generator::LoadInputFileProcessStep load_input_file_process_step(process_context);
    steps.push_back(&load_input_file_process_step);

    // Step 3 - Apply Filter (Position)
    //

    // Step 4 - Apply Filter (Orientation)
    //

    // following lines are just for TESTING PURPOSE
    /*
    kuka_generator::DataRow test1;
    test1.position_filtered.x = 1;
    test1.position_filtered.y = 2;
    test1.position_filtered.z = 3;
    process_context.data_rows.push_back(test1);

    kuka_generator::DataRow test2;
    test2.position_filtered.x = 2;
    test2.position_filtered.y = 2;
    test2.position_filtered.z = 3;
    process_context.data_rows.push_back(test2);

    kuka_generator::DataRow test3;
    test3.position_filtered.x = 3;
    test3.position_filtered.y = 2;
    test3.position_filtered.z = 3;
    process_context.data_rows.push_back(test3);

    kuka_generator::DataRow test4;
    test4.position_filtered.x = 3;
    test4.position_filtered.y = 15;
    test4.position_filtered.z = 3;
    process_context.data_rows.push_back(test4);

    kuka_generator::DataRow test5;
    test5.position_filtered.x = 13;
    test5.position_filtered.y = 20;
    test5.position_filtered.z = 3;
    process_context.data_rows.push_back(test5);

    kuka_generator::DataRow test6;
    test6.position_filtered.x = 16;
    test6.position_filtered.y = 20;
    test6.position_filtered.z = 3;
    process_context.data_rows.push_back(test6);

    kuka_generator::DataRow test7;
    test7.position_filtered.x = 20;
    test7.position_filtered.y = 20;
    test7.position_filtered.z = 3;
    process_context.data_rows.push_back(test7);

    std::vector<kuka_generator::DataRow>::iterator it = process_context.data_rows.begin() +6;
    */

    // Step 5 - Douglas Peucker (3D)
    // The Varible DP is given the adress of process_context, the first element, the last element
    // and the tolerance (width of the DP Line) in
    // which the points are allowed to be without creating a new corner point

    kuka_generator::CDP DP;
    DP.DPRecursive(&process_context, process_context.data_rows.begin(), process_context.data_rows.end(), 5.0);

    // this following line is just for TESTING PURPOSE | if the line is used (testing) the line above must be commended out
    //DP.DPRecursive(&process_context, process_context.data_rows.begin(), it, 5.0);
    


    // Step 6 - Umrechnung Orientierungsmatrix in Euler Winkel
    //

    // Step 7 - Berechnung der Geschwindigkeit
    //

    // Step 8 - Ausgabe in KUKA KRL (.src)
    //

    //
    // Execute the process
    //

    // for-loop over all steps stored in the steps vector and execute each step
    for (auto step : steps)
    {
        // run the step. The process context is already supplied when creating the process step variable via the constructor!
        step->process();
    }

    return 0;
}
