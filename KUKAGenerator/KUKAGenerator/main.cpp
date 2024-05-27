#include <ctime>
#include <iostream>
#include <valarray>

#include <ExampleProcessStep.h>
#include <IProcessStep.h>
#include <LoadInputFileProcessStep.h>
#include <ProcessContext.h>


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

    // Step 5 - Douglas Peucker (3D)
    //

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
