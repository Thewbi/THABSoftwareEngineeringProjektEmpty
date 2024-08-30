#pragma once

#include <iostream>
#include <algorithm>

#include <IProcessStep.h>
#include <ProcessContext.h>

namespace kuka_generator
{
    class EulerAnglesProcessStep : public IProcessStep
    {

    private:

        /// <summary>
        /// The process context to add data into. Used to indirectly interact with other steps.
        /// </summary>
        kuka_generator::ProcessContext& process_context_;

        double pi = 3.14159265358979323846;
        int index = 0;

    public:

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="process_context">The process context</param>
        EulerAnglesProcessStep (kuka_generator::ProcessContext& process_context);

    
        /// <summary>
        /// Run this process
        /// </summary>
        int process() override;
    };
}


    

