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

        virtual void trace(const std::string line) = 0;

    };
}
