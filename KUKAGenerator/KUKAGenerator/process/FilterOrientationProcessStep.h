#pragma once

#include <iostream>
#include <algorithm>

#include <IProcessStep.h>
#include <ProcessContext.h>

namespace kuka_generator
{

    /// <summary>
    /// This is an example. It can be used as a template for process steps.
    /// </summary>
    class FilterOrientationProcessStep : public IProcessStep
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
        FilterOrientationProcessStep(kuka_generator::ProcessContext& process_context);

        /// <summary>
        /// Run this process
        /// </summary>
        int process() override;

    };

}
