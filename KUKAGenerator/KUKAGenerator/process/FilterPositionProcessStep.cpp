#include <FilterPositionProcessStep.h>

kuka_generator::FilterPositionProcessStep::FilterPositionProcessStep(kuka_generator::ProcessContext& process_context)
    : process_context_(process_context)
{
    // empty
}

int kuka_generator::FilterPositionProcessStep::process()
{
    if (process_context_.length_filter_position <= 1)
    {
        // if the filter length is at most a single data_row, no filtering takes places
        for (DataRow& data_row : process_context_.data_rows)
        {
            // copy the data_row over
            data_row.position_filtered = data_row.position;
        }
    }
    else
    {
        // if more than a single data_row will be part of the filter window
        // iterate over the last n data_row leading up to the current data_row
        uint16_t idx = 0;
        for (DataRow& data_row : process_context_.data_rows)
        {
            Vector3d position_accum;
            double elements = 0;

            // iterate over the last n data_rows.
            // if there are less elements available, just iterate over less elements
            uint16_t accum_index = std::max(idx - process_context_.length_filter_position + 1, 0);
            for (uint16_t i = accum_index; i <= idx; i++)
            {
                // pick the current data_row
                DataRow current_data_row = process_context_.data_rows.at(i);

                position_accum.x += current_data_row.position.x;
                position_accum.y += current_data_row.position.y;
                position_accum.z += current_data_row.position.z;

                elements++;
            }

            position_accum.x /= elements;
            position_accum.y /= elements;
            position_accum.z /= elements;

            data_row.position_filtered = position_accum;

            idx++;
        }
    }

    return NO_ERROR_RESULT;
}
