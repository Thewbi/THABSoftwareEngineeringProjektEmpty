#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>

#include <IProcessStep.h>
#include <float_math.h>

namespace fs = std::filesystem;

namespace kuka_generator
{
    /// <summary>
    /// Outputs the process context into a KUKA KRL (.src)
    /// The output file path is taken from the process context.
    /// </summary>
    class OutputToKUKASrcFileProcessStep : public IProcessStep
    {

    private:

        /// <summary>
        /// The process context to add data into. Used to indirectly interact with other steps.
        /// </summary>
        kuka_generator::ProcessContext& process_context_;

    public:

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="process_context">The process context</param>
        OutputToKUKASrcFileProcessStep(kuka_generator::ProcessContext& process_context);

        /// <summary>
        /// Run this process step
        /// </summary>
        int process() override;
    };

}
