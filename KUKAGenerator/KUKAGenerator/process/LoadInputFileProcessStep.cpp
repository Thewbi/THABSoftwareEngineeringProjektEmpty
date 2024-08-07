#include <LoadInputFileProcessStep.h>

namespace kuka_generator
{
    LoadInputFileProcessStep::LoadInputFileProcessStep(kuka_generator::ProcessContext& process_context) : process_context_(process_context)
    {
        // empty
    }

    int LoadInputFileProcessStep::process()
    {
        std::cout << "[LoadInputFileProcessStep] Reading file '" << process_context_.input_file << "'" << std::endl;

        // the line reader takes care of the file handling
        // Every line will be sent to the process_line_callback function
        kuka_generator::ToLineFileReader to_line_file_reader(process_context_.input_file, *this);
        int result = to_line_file_reader.process();

        if (result == kuka_generator::NO_ERROR_RESULT)
        {
            std::cout << "[LoadInputFileProcessStep] [SUCCESS] Reading file done!" << std::endl;
        }
        else
        {
            std::cout << "[LoadInputFileProcessStep] [ERROR] Reading file failed!" << std::endl;
        }

        return result;
    }

    void LoadInputFileProcessStep::process_line_callback(std::string line)
    {
        // convert the line to a data row
        kuka_generator::DataRow data_row;
        converter_.convert(line, data_row);

        data_row.index = process_context_.data_rows.size();

        // store the data row
        process_context_.data_rows.push_back(data_row);
    }

}
