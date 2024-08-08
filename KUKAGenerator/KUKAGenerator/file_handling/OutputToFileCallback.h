#pragma once

#include <string>

#include <IOutputToFileCallback.h>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace kuka_generator
{
    /// <summary>
    /// This is the implementation of the IOutputToFileCallback interface.
    ///
    /// https://stackoverflow.com/questions/318064/how-do-you-declare-an-interface-in-c
    /// </summary>
    class OutputToFileCallback : public IOutputToFileCallback
    {

    private:

        std::ofstream ofstream;

    public:

        /// <summary>
        /// Creates folders contained in the path
        /// </summary>
        /// <param name="filepath"></param>
        void create_folders(std::string filepath) override;

        /// <summary>
        /// Opens a file
        /// </summary>
        /// <param name="filepath"></param>
        void open_file(std::string filepath) override;

        /// <summary>
        /// Output a line to the file
        /// </summary>
        /// <param name="line">a line read from the input file</param>
        void output_line(std::string line) override;

        /// <summary>
        /// Close the file
        /// </summary>
        void close_file() override;

    };
}
