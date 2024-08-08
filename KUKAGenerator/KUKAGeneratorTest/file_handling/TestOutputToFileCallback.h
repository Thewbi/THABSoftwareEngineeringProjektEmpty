#pragma once

#include <string>
#include <iostream>
#include <vector>

#include <IOutputToFileCallback.h>

namespace kuka_generator
{
    class TestOutputToFileCallback : public kuka_generator::IOutputToFileCallback
    {
    public:
        std::vector<std::string> data;

        std::string filepath;

        std::string open_file_path;

        bool close_file_called{ false };

        /// <summary>
        /// Creates folders in the filepath
        /// </summary>
        /// <param name="filepath">The file path</param>
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
