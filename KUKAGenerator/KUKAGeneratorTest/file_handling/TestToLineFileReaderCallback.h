#pragma once

#include <string>
#include <iostream>

#include <IToLineFileReaderCallback.h>

namespace kuka_generator
{
    class TestToLineFileReaderCallback : public kuka_generator::IToLineFileReaderCallback
    {
    public:
        std::vector<std::string> data;

        void TestToLineFileReaderCallback::process_line_callback(std::string line);
    };
}
