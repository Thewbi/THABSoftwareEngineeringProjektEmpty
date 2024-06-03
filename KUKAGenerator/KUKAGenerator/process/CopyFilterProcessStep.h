#pragma once

#include <iostream>

#include <IProcessStep.h>
#include <IToLineFileReaderCallback.h>
#include <ProcessContext.h>
#include <StringToDataRowConverter.h>
#include <ToLineFileReader.h>

namespace kuka_generator
{

    /// <summary>
    /// This is an example filter. It just performs a copy without any real filtering.
    /// </summary>
    class CopyFilterProcessStep : public IProcessStep
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
        CopyFilterProcessStep(kuka_generator::ProcessContext& process_context);

        /// <summary>
        /// Run this process
        /// </summary>
        void process() override;

    };

}
