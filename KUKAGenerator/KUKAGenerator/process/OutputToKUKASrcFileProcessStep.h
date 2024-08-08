#pragma once

#include <iostream>
#include <sstream>

#include <IProcessStep.h>
#include <IOutputToFileCallback.h>
#include <float_math.h>

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

        /// <summary>
        /// The callback for file handling.
        /// </summary>
        IOutputToFileCallback& output_to_file_callback_;

        /// <summary>
        /// Output the velocity to the file
        /// </summary>
        /// <param name="velocity">the velocity to output</param>
        void output_velocity(const float velocity);

    public:

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="process_context">The process context</param>
        /// <param name="output_to_file_callback">The output_to_file_callback</param>
        OutputToKUKASrcFileProcessStep(kuka_generator::ProcessContext& process_context,
            IOutputToFileCallback& output_to_file_callback);

        /// <summary>
        /// Run this process step
        /// </summary>
        int process() override;
    };

}
