#include <OutputToKUKASrcFileProcessStep.h>

namespace kuka_generator
{
    OutputToKUKASrcFileProcessStep::OutputToKUKASrcFileProcessStep(kuka_generator::ProcessContext& process_context) : process_context_(process_context)
    {
        // empty
    }

    int OutputToKUKASrcFileProcessStep::process()
    {
        int result = kuka_generator::NO_ERROR_RESULT;

        // if there is not data to output, abort this step
        if (process_context_.data_rows.size() == 0)
        {
            std::cout << "[OutputToKUKASrcFileProcessStep] No data in process context to write!" << std::endl;
            return result;
        }

        // https://stackoverflow.com/questions/62256738/visual-studio-2019-c-and-stdfilesystem
        //
        // Create the path that the user has selected via the user interface
        const fs::path path = process_context_.output_file;
        const fs::path parent_path = path.parent_path();
        create_directories(parent_path);

        std::cout << "[OutputToKUKASrcFileProcessStep] Writing file '" << process_context_.output_file << "'" << std::endl;

        std::ofstream ofstream(path);
        ofstream.precision(6);
        ofstream << std::fixed;

        // output DEF 09_robCode
        ofstream << "DEF 09_robCode\n";

        // PTP $POS_ACT
        ofstream << "PTP $POS_ACT\n";

        // output velocity
        float velocity = process_context_.data_rows.at(0).velocity;
        ofstream << "$VEL.CP=" << velocity << "\n";

        for (auto& data_row : process_context_.data_rows)
        {
            if (!data_row.alive)
            {
                continue;
            }



            float pos_x = data_row.position_filtered.x;
            float pos_y = data_row.position_filtered.y;
            float pos_z = data_row.position_filtered.z;

            float euler_a = data_row.euler_angles.x;
            float euler_b = data_row.euler_angles.y;
            float euler_c = data_row.euler_angles.z;

            ofstream << "LIN {X " << pos_x << ", Y " << pos_y << ", Z " << pos_z << ", A " << euler_a << "" << ", B " << euler_b << ", C " << euler_c << "} \n";

            //if (velocity != data_row.velocity)
            if (!float_compare(velocity, data_row.velocity))
            {
                velocity = data_row.velocity;

                // output velocity
                ofstream << "$VEL.CP=" << velocity << "\n";
            }
        }

        ofstream.flush();
        ofstream.close();

        std::cout << "[OutputToKUKASrcFileProcessStep] [SUCCESS] Writing file done!" << std::endl;

        return result;
    }
}
