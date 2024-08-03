#include "pch.h"
#include <vector>
#include <TestToLineFileReaderCallback.h>

namespace kuka_generator
{

    void TestToLineFileReaderCallback::process_line_callback(std::string line)
    {
        //std::cout << "line" << std::endl;
        data.push_back(line);
    }

}
