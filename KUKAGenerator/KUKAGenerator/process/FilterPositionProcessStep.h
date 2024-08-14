#pragma once

#include <iostream>
#include <algorithm>

#include <IProcessStep.h>
#include <ProcessContext.h>

namespace kuka_generator
{

    /// <summary>
    /// This step performs filtering over posistion data of the each position
    /// information and it's n predecessors. The average position is constructed.
    /// Average position means x, y and z coordinates are summed up respectively
    /// and the three results are ach divided by n. The three averaged components
    /// form the filtered position.
    ///
    /// The parameter n is taken from the user interface. 
    /// </summary>
    class FilterPositionProcessStep : public IProcessStep
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
        FilterPositionProcessStep(kuka_generator::ProcessContext& process_context);

        /// <summary>
        /// Run this process
        /// </summary>
        int process() override;

    };

}
