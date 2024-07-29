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
    /// Loads a .csv input file and parses all contained rows.
    /// Fills the process context with the extracted information.
    /// </summary>
    class LoadInputFileProcessStep : public IProcessStep, public IToLineFileReaderCallback
    {

    private:

        /// <summary>
        /// The process context to add data into. Used to indirectly interact with other steps.
        /// </summary>
        kuka_generator::ProcessContext& process_context_;

        /// <summary>
        /// This converter is used to convert a line from the input file into a DataRow.
        /// </summary>
        kuka_generator::StringToDataRowConverter converter_;

    public:

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="process_context">The process context</param>
        LoadInputFileProcessStep(kuka_generator::ProcessContext& process_context);

        /// <summary>
        /// Run this process step
        /// </summary>
        int process() override;

        /// <summary>
        /// This specific process step implements the IToLineFileReaderCallback interface
        /// so it can register itself as a callback to the ToLineFileReader because it
        /// has to convert lines to DataRows.
        /// </summary>
        /// <param name="line">The line that was read from the file.</param>
        void process_line_callback(std::string line) override;

    };
}
