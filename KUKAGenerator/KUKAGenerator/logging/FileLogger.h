#pragma once

#include <string>

#include <ILogger.h>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace kuka_generator
{
    /// <summary>
    /// This is the implementation of the ILogger interface for logging to files
    /// </summary>
    class FileLogger : public ILogger
    {

    private:

        /// <summary>
        /// The file to place output into.
        /// </summary>
        std::ofstream ofstream;

    public:

        /// <summary>
        /// Only produces output if this flag is set to true.
        /// </summary>
        bool active{ false };

    public:

        /// <summary>
        /// Output a line to the file using trace level.
        /// </summary>
        /// <param name="line">a line to trace into the file</param>
        void trace(std::string line) override;

        /// <summary>
        /// Write out buffered data.
        /// </summary>
        void flush() override;

        /// <summary>
        /// Creates folders contained in the path
        /// </summary>
        /// <param name="filepath"></param>
        void create_folders(std::string filepath);

        /// <summary>
        /// Opens a file
        /// </summary>
        /// <param name="filepath"></param>
        void open_file(std::string filepath);

        /// <summary>
        /// Close the file
        /// </summary>
        void close_file();

    };
}
