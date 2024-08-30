#include "Euler.h"
#include <double_math.h>

namespace kuka_generator
{
    // this constructor places the process_context into the member variable called
    // process_context_ via the so-called initializer list. The initializer list are
    // all the statements after the colon.
    // process_context_(process_context) means that process_context_ is set to the procese_context parameter.
    EulerAnglesProcessStep::EulerAnglesProcessStep(kuka_generator::ProcessContext& process_context) : process_context_(process_context)
    {
        // empty
    }

    int EulerAnglesProcessStep::process()
    {
        std::cout << "Step 6 - Euler Angles calculation has started." << std::endl;
       
        for (DataRow& data_row : process_context_.data_rows)    //range basierte for Schleife
        {
            //Alle 3 Winkel mit Wert 0 initialisieren
            data_row.euler_angles.x = 0.0;
            data_row.euler_angles.y = 0.0;
            data_row.euler_angles.z = 0.0;

            if (data_row.orientation_filtered[6] == -1)
            {
                std::cout << "Ausnahme: Wert R31 von Element " << index; std::cout << " = -1!" << std::endl;     //Fall 1: R31 = -1

                // A = 0
                data_row.euler_angles.x = 0;

                // B = Pi/2 in Grad
                data_row.euler_angles.y = (pi / 2) * (180.0f / pi);

                // C = atan2 R12, R13 in Grad
                data_row.euler_angles.z = 1.0 * atan2(data_row.orientation_filtered[1], data_row.orientation_filtered[2]);
                data_row.euler_angles.z = data_row.euler_angles.z * 180.0f / pi;
                data_row.euler_angles.z = to_positive_angle(data_row.euler_angles.z);
            }
            else if (data_row.orientation_filtered[6] == 1)
            {
                std::cout << "Ausnahme: Wert R31 von Element " << index; std::cout << " = 1!" << std::endl;      //Fall 2: R31 = 1

                // A = 0
                data_row.euler_angles.x = 0;

                // B = -1* Pi/2 in Grad
                data_row.euler_angles.y = -1.0 * (pi / 2) * (180.0f / pi);

                // C = atan2 -R12, -R13 in Grad
                data_row.euler_angles.z = 1.0 * atan2(-1.0 * data_row.orientation_filtered[1], -1.0 * data_row.orientation_filtered[2]);
                data_row.euler_angles.z = data_row.euler_angles.z * 180.0f / pi;
                data_row.euler_angles.z = to_positive_angle(data_row.euler_angles.z);
            }
            else
            {
                //  R11 [0] R12 [1] R13 [2]
                //  R21 [3] R22 [4] R23 [5]
                //  R31 [6] R32 [7] R33 [8]

                // B = −asin R31 in Grad
                data_row.euler_angles.y = -1.0 * asin(data_row.orientation_filtered[6]);
                data_row.euler_angles.y = data_row.euler_angles.y * 180 / pi;
                data_row.euler_angles.y = to_positive_angle(data_row.euler_angles.y);

                // A = atan2 R21, R11 in Grad
                data_row.euler_angles.x = 1.0 * atan2(data_row.orientation_filtered[3], data_row.orientation_filtered[0]);
                data_row.euler_angles.x = data_row.euler_angles.x * 180 / pi;
                data_row.euler_angles.x = to_positive_angle(data_row.euler_angles.x);

                // C = atan2 R32, R33 in Grad
                data_row.euler_angles.z = 1.0 * atan2(data_row.orientation_filtered[7], data_row.orientation_filtered[8]);
                data_row.euler_angles.z = data_row.euler_angles.z * 180.0f / pi;
                data_row.euler_angles.z = to_positive_angle(data_row.euler_angles.z);
            }

        index++;
        }

        std::cout << "Step 6 - Euler Angles calculation has finished." << std::endl << std::endl;
        return NO_ERROR_RESULT;
    }
}
