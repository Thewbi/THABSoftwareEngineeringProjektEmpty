#include <OutputToFileCallback.h>

void kuka_generator::OutputToFileCallback::create_folders(std::string filepath)
{
    // https://stackoverflow.com/questions/62256738/visual-studio-2019-c-and-stdfilesystem
    //
    // Create the path that the user has selected via the user interface
    const fs::path path = filepath;
    const fs::path parent_path = path.parent_path();
    create_directories(parent_path);
}

void kuka_generator::OutputToFileCallback::open_file(std::string filepath)
{
    ofstream = std::ofstream(filepath);
    ofstream.precision(6);
    ofstream << std::fixed;
}

void kuka_generator::OutputToFileCallback::output_line(std::string line)
{
    ofstream << line;
}

void kuka_generator::OutputToFileCallback::close_file()
{
    ofstream.flush();
    ofstream.close();
}
