#include <CopyFilterProcessStep.h>

namespace kuka_generator
{
    // this constructor places the process_context into the member variable called
    // process_context_ via the so-called initializer list. The initializer list are
    // all the statements after the colon.
    //
    // process_context_(process_context) means that process_context_ is set to the procese_context parameter.
    CopyFilterProcessStep::CopyFilterProcessStep(kuka_generator::ProcessContext& process_context) : process_context_(process_context)
    {
        // empty
    }

    int CopyFilterProcessStep::process()
    {
        std::cout << "[CopyFilterProcessStep] start processing!" << std::endl;

        for (auto& data_row : process_context_.data_rows)
        {
            data_row.position_filtered = data_row.position;
        }

        std::cout << "[CopyFilterProcessStep] done!" << std::endl;

        return NO_ERROR_RESULT;
    }

}
