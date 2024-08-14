#include <FilterOrientationProcessStep.h>

kuka_generator::FilterOrientationProcessStep::FilterOrientationProcessStep(kuka_generator::ProcessContext& process_context)
    : process_context_(process_context)
{
    // empty
}

int kuka_generator::FilterOrientationProcessStep::process()
{
    if (process_context_.use_user_defined_orientation)
    {
        // if the user wants to use their own rotation, put the user defined
        // orientation into all orientations
        for (DataRow& data_row : process_context_.data_rows)
        {
            // copy the user defined orientation over
            data_row.orientation_filtered = process_context_.user_defined_orientation;
        }
    }
    else if (process_context_.length_filter_orientation <= 1)
    {
        // if the filter length is at most a single data_row, no filtering takes places
        for (DataRow& data_row : process_context_.data_rows)
        {
            // copy the data_row over
            data_row.orientation_filtered = data_row.orientation;
        }
    }
    else
    {
        // if more than a single data_row will be part of the filter window
        // iterate over the last n data_row leading up to the current data_row
        uint16_t idx = 0;
        for (DataRow& data_row : process_context_.data_rows)
        {
            // allocate space for the first and second column of the accumulated orientation matrix
            Vector3d first_column_accum;
            Vector3d second_column_accum;

            // iterate over the last n data_rows.
            // if there are less elements available, just iterate over less elements
            uint16_t accum_index = std::max(idx - process_context_.length_filter_orientation + 1, 0);
            for (uint16_t i = accum_index; i <= idx; i++)
            {
                // pick the current data_row
                DataRow current_data_row = process_context_.data_rows.at(i);

                first_column_accum.x += current_data_row.orientation.data[0];
                first_column_accum.y += current_data_row.orientation.data[3];
                first_column_accum.z += current_data_row.orientation.data[6];

                second_column_accum.x += current_data_row.orientation.data[1];
                second_column_accum.y += current_data_row.orientation.data[4];
                second_column_accum.z += current_data_row.orientation.data[7];
            }

            // build all three vectors of the new, filtered orientation matrix
            first_column_accum.normalize();
            second_column_accum.normalize();
            Vector3d third_column = first_column_accum.cross_product(second_column_accum);
            third_column.normalize();

            // assemble the new, filtered orientation matrix
            data_row.orientation_filtered.data[0] = first_column_accum.x;
            data_row.orientation_filtered.data[3] = first_column_accum.y;
            data_row.orientation_filtered.data[6] = first_column_accum.z;

            data_row.orientation_filtered.data[1] = second_column_accum.x;
            data_row.orientation_filtered.data[4] = second_column_accum.y;
            data_row.orientation_filtered.data[7] = second_column_accum.z;

            data_row.orientation_filtered.data[2] = third_column.x;
            data_row.orientation_filtered.data[5] = third_column.y;
            data_row.orientation_filtered.data[8] = third_column.z;

            idx++;
        }
    }

    return NO_ERROR_RESULT;
}
