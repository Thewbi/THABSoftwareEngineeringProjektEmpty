#include "pch.h"
#include <TestOutputToFileCallback.h>

void kuka_generator::TestOutputToFileCallback::create_folders(std::string filepath)
{
    this->filepath = filepath;
}

void kuka_generator::TestOutputToFileCallback::open_file(std::string open_file)
{
    this->open_file_path = open_file;
}

void kuka_generator::TestOutputToFileCallback::output_line(std::string line)
{
    this->data.push_back(line);
}

void kuka_generator::TestOutputToFileCallback::close_file()
{
    this->close_file_called = true;
}
