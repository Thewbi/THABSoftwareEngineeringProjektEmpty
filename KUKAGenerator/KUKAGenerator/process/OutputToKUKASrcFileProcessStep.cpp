#include <OutputToKUKASrcFileProcessStep.h>

namespace kuka_generator
{
    OutputToKUKASrcFileProcessStep::OutputToKUKASrcFileProcessStep(
        ProcessContext& process_context,
        IOutputToFileCallback& output_to_file_callback)
        : process_context_(process_context), output_to_file_callback_(output_to_file_callback)
    {
        // empty
    }

    void OutputToKUKASrcFileProcessStep::output_velocity(const float velocity)
    {
        std::stringstream sstream;
        sstream.precision(6);
        sstream << std::fixed;
        sstream << "$VEL.CP=" << velocity << "\n";
        output_to_file_callback_.output_line(sstream.str());
    }

    int OutputToKUKASrcFileProcessStep::process()
    {
        int result = kuka_generator::NO_ERROR_RESULT;

        // if there is not data to output, abort this step
        if (process_context_.data_rows.size() == 0)
        {
            std::cout << "[OutputToKUKASrcFileProcessStep] No data in process context to write! Aborting!" << std::endl;
            return -1;
        }

        if (process_context_.output_file.empty())
        {
            std::cout << "[OutputToKUKASrcFileProcessStep] No output file specified! Aborting!" << std::endl;
            return -2;
        }

        output_to_file_callback_.create_folders(process_context_.output_file);

        std::cout << "[OutputToKUKASrcFileProcessStep] Writing file '" << process_context_.output_file << "'" << std::endl;

        output_to_file_callback_.open_file(process_context_.output_file);

        // output DEF <SCRIPT_NAME>
        std::stringstream script_name_sstream;
        script_name_sstream << "DEF " << process_context_.output_file << "\n";
        output_to_file_callback_.output_line(script_name_sstream.str());

        // PTP $POS_ACT
        output_to_file_callback_.output_line("PTP $POS_ACT\n");

        // output velocity
        float velocity = process_context_.data_rows.at(0).velocity;
        output_velocity(velocity);

        for (auto& data_row : process_context_.data_rows)
        {
            if (!data_row.alive)
            {
                continue;
            }

            // do not output the velocity if it is already set or if it is zero
            if (!float_compare(velocity, data_row.velocity) && !float_compare(0.0, data_row.velocity))
            {
                // output velocity
                output_velocity(data_row.velocity);

                // remember this velocity for the next iteration
                velocity = data_row.velocity;
            }

            double pos_x = data_row.position_filtered.x;
            double pos_y = data_row.position_filtered.y;
            double pos_z = data_row.position_filtered.z;

            // sensical default values so that the FIREBRAND simulator works
            double euler_a = 0.0;
            double euler_b = 180.0;
            double euler_c = 0.0;

            // override default values if there are computed values to override the defaults with
            if (data_row.euler_angles.x != 0.0 || data_row.euler_angles.y != 0.0 || data_row.euler_angles.z != 0.0)
            {
                euler_a = data_row.euler_angles.x;
                euler_b = data_row.euler_angles.y;
                euler_c = data_row.euler_angles.z;
            }

            std::stringstream sstream;
            sstream.precision(6);
            sstream << std::fixed;
            sstream << "LIN {X " << pos_x << ", Y " << pos_y << ", Z " << pos_z << ", A " << euler_a << "" << ", B " << euler_b << ", C " << euler_c << "} \n";
            output_to_file_callback_.output_line(sstream.str());
        }

        output_velocity(0.0);

        output_to_file_callback_.output_line("END");

        output_to_file_callback_.close_file();

        std::cout << "[OutputToKUKASrcFileProcessStep] [SUCCESS] Writing file done!" << std::endl;

        return result;
    }
}
