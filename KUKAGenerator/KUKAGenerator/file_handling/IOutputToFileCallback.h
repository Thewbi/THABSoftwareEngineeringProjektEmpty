#pragma once

#include <string>

namespace kuka_generator
{
    /// <summary>
    /// This is the "interface" that has to be implemented by each OutputToFileCallback.
    ///
    /// https://stackoverflow.com/questions/318064/how-do-you-declare-an-interface-in-c
    /// </summary>
    class IOutputToFileCallback
    {

    public:

        virtual ~IOutputToFileCallback() {}

        /// <summary>
        /// Creates folders contained in the path
        /// </summary>
        /// <param name="filepath"></param>
        virtual void create_folders(std::string filepath) = 0;

        /// <summary>
        /// Opens a file
        /// </summary>
        /// <param name="filepath"></param>
        virtual void open_file(std::string filepath) = 0;

        /// <summary>
        /// Output a line to the file
        /// </summary>
        /// <param name="line">a line read from the input file</param>
        virtual void output_line(std::string line) = 0;

        /// <summary>
        /// Close the file
        /// </summary>
        virtual void close_file() = 0;

    };
}
