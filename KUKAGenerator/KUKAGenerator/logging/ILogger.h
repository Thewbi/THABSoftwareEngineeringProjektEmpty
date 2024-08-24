#pragma once

#include <string>

namespace kuka_generator
{
    /// <summary>
    /// This is the "interface" that has to be implemented by each Logger.
    /// </summary>
    class ILogger
    {

    public:

        virtual ~ILogger() {}

        /// <summary>
        /// Output a line using trace level.
        /// </summary>
        /// <param name="line">a line to trace into the destination</param>
        virtual void trace(const std::string line) = 0;

        /// <summary>
        /// Write out buffered data.
        /// </summary>
        virtual void flush() = 0;

    };
}
