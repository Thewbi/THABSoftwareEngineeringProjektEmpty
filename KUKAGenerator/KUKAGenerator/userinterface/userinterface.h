#pragma once

#include <cctype>
#include <iostream>
#include <iostream>
#include <sstream>
#include <string>

#include <string>
#include <windows.h>

#include <IProcessStep.h>
#include <ProcessContext.h>

namespace kuka_generator
{

    /// <summary>
    /// This is an example. It can be used as a template for process steps.
    /// </summary>
    class Userinterface : public IProcessStep
    {

    private:

        /// <summary>
        /// The process context to add data into. Used to indirectly interact with other steps.
        /// </summary>
        kuka_generator::ProcessContext& process_context_;

        std::string user_input_file; // variable to store path to inputfile 
        std::string user_output_file; // variable to store path for outputfile
        std::string user_defined_oriantation_mode; // variable to store userselection for orientationmode
        std::string user_defined_orientation; // variable to store userselection for orientation
        std::string user_defined_velocity_mode; // variable to store userselection for velocitymode
        std::string user_defined_velocity; // variable to store userselection for velocity
        std::string user_defined_filter_orientation; // variable to store userselection for orientationfilter
        std::string user_defined_filter_position; // variable to store userselection for positionfilter

    public:

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="process_context">The process context</param>
        Userinterface(kuka_generator::ProcessContext& process_context);
        int checkinput(std::string& user_input);
        int checkpath(std::string& user_input);
        int checkint(std::string& user_input);
        int checkdouble(std::string& user_input);

        /// <summary>
        /// Run this process
        /// </summary>
        int process() override;

    };

}
