#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

#include <FilterOrientationProcessStep.h>
#include <float_math.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// https://stackoverflow.com/questions/25150708/how-to-get-the-projectdir-path-in-a-visual-studio-native-c-unit-testing-usi
#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)

namespace FilterOrientationProcessStepTest
{

    /// <summary>
    /// https://learn.microsoft.com/de-de/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2022#general_is_True
    /// </summary>
    TEST_CLASS(FilterOrientationProcessStepTest)
    {

    public:

        TEST_METHOD(Filter_Data_Empty_Test)
        {
            // Arrange

            kuka_generator::ProcessContext process_context;
            process_context.length_filter_orientation = 100;

            kuka_generator::FilterOrientationProcessStep filter_orientation_process_step(process_context);

            // Act

            int result = filter_orientation_process_step.process();

            // Assert

            // no error occured
            Assert::AreEqual(kuka_generator::NO_ERROR_RESULT, result);
        }

        TEST_METHOD(FilterWindowLength_1_Test)
        {
            // Arrange

            kuka_generator::DataRow data_row;
            data_row.alive = true;
            for (int i = 0; i < 9; i++)
            {
                data_row.orientation.data[i] = i;
            }

            kuka_generator::ProcessContext process_context;
            process_context.data_rows.push_back(data_row);
            process_context.length_filter_orientation = 1;

            kuka_generator::FilterOrientationProcessStep filter_orientation_process_step(process_context);

            // Act

            int result = filter_orientation_process_step.process();

            // Assert

            // the filtered value is the same as the original data since the window has a size of 1
            for (int i = 0; i < 9; i++)
            {
                Assert::AreEqual((double)i, process_context.data_rows.at(0).orientation_filtered.data[i]);
            }

            // no error occured
            Assert::AreEqual(kuka_generator::NO_ERROR_RESULT, result);
        }

        TEST_METHOD(Use_UserOrientation_Test)
        {
            // Arrange

            kuka_generator::DataRow data_row;
            data_row.alive = true;
            for (int i = 0; i < 9; i++)
            {
                data_row.orientation.data[i] = i;
            }

            kuka_generator::ProcessContext process_context;
            process_context.data_rows.push_back(data_row);
            process_context.length_filter_orientation = 1;
            process_context.use_user_defined_orientation = true;
            process_context.user_defined_orientation.data[0] = 30.0;
            process_context.user_defined_orientation.data[1] = 29.0;
            process_context.user_defined_orientation.data[2] = 28.0;
            process_context.user_defined_orientation.data[3] = 27.0;
            process_context.user_defined_orientation.data[4] = 26.0;
            process_context.user_defined_orientation.data[5] = 25.0;
            process_context.user_defined_orientation.data[6] = 24.0;
            process_context.user_defined_orientation.data[7] = 23.0;
            process_context.user_defined_orientation.data[8] = 22.0;

            kuka_generator::FilterOrientationProcessStep filter_orientation_process_step(process_context);

            // Act

            int result = filter_orientation_process_step.process();

            // Assert

            Assert::AreEqual(30.0, process_context.data_rows.at(0).orientation_filtered.data[0]);
            Assert::AreEqual(29.0, process_context.data_rows.at(0).orientation_filtered.data[1]);
            Assert::AreEqual(28.0, process_context.data_rows.at(0).orientation_filtered.data[2]);
            Assert::AreEqual(27.0, process_context.data_rows.at(0).orientation_filtered.data[3]);
            Assert::AreEqual(26.0, process_context.data_rows.at(0).orientation_filtered.data[4]);
            Assert::AreEqual(25.0, process_context.data_rows.at(0).orientation_filtered.data[5]);
            Assert::AreEqual(24.0, process_context.data_rows.at(0).orientation_filtered.data[6]);
            Assert::AreEqual(23.0, process_context.data_rows.at(0).orientation_filtered.data[7]);
            Assert::AreEqual(22.0, process_context.data_rows.at(0).orientation_filtered.data[8]);

            // no error occured
            Assert::AreEqual(kuka_generator::NO_ERROR_RESULT, result);
        }

        TEST_METHOD(FilterWindowLength_window_size_3_Test)
        {
            // Arrange

            kuka_generator::ProcessContext process_context;

            kuka_generator::DataRow data_row;
            data_row.alive = true;

            data_row.orientation.data[0] = 1.0;
            data_row.orientation.data[1] = 1.0;
            data_row.orientation.data[2] = 1.0;
            data_row.orientation.data[3] = 1.0;
            data_row.orientation.data[4] = 1.0;
            data_row.orientation.data[5] = 1.0;
            data_row.orientation.data[6] = 1.0;
            data_row.orientation.data[7] = 1.0;
            data_row.orientation.data[8] = 1.0;
            process_context.data_rows.push_back(data_row);

            data_row.orientation.data[0] = 2.0;
            data_row.orientation.data[1] = 2.0;
            data_row.orientation.data[2] = 2.0;
            data_row.orientation.data[3] = 2.0;
            data_row.orientation.data[4] = 2.0;
            data_row.orientation.data[5] = 2.0;
            data_row.orientation.data[6] = 2.0;
            data_row.orientation.data[7] = 2.0;
            data_row.orientation.data[8] = 2.0;
            process_context.data_rows.push_back(data_row);

            data_row.orientation.data[0] = 3.0;
            data_row.orientation.data[1] = 3.0;
            data_row.orientation.data[2] = 3.0;
            data_row.orientation.data[3] = 3.0;
            data_row.orientation.data[4] = 3.0;
            data_row.orientation.data[5] = 3.0;
            data_row.orientation.data[6] = 3.0;
            data_row.orientation.data[7] = 3.0;
            data_row.orientation.data[8] = 3.0;
            process_context.data_rows.push_back(data_row);

            data_row.orientation.data[0] = 4.0;
            data_row.orientation.data[1] = 4.0;
            data_row.orientation.data[2] = 4.0;
            data_row.orientation.data[3] = 4.0;
            data_row.orientation.data[4] = 4.0;
            data_row.orientation.data[5] = 4.0;
            data_row.orientation.data[6] = 4.0;
            data_row.orientation.data[7] = 4.0;
            data_row.orientation.data[8] = 4.0;
            process_context.data_rows.push_back(data_row);

            data_row.orientation.data[0] = 5.0;
            data_row.orientation.data[1] = 5.0;
            data_row.orientation.data[2] = 5.0;
            data_row.orientation.data[3] = 5.0;
            data_row.orientation.data[4] = 5.0;
            data_row.orientation.data[5] = 5.0;
            data_row.orientation.data[6] = 5.0;
            data_row.orientation.data[7] = 5.0;
            data_row.orientation.data[8] = 5.0;
            process_context.data_rows.push_back(data_row);

            process_context.length_filter_orientation = 3;

            kuka_generator::FilterOrientationProcessStep filter_orientation_process_step(process_context);

            // Act

            int result = filter_orientation_process_step.process();

            // Assert

            // the filtered value is the same as the original data since the window has a size of 1
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(0).orientation_filtered.data[0]));
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(0).orientation_filtered.data[1]));
            Assert::AreEqual(0.0, process_context.data_rows.at(0).orientation_filtered.data[2]);
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(0).orientation_filtered.data[3]));
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(0).orientation_filtered.data[4]));
            Assert::AreEqual(0.0, process_context.data_rows.at(0).orientation_filtered.data[5]);
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(0).orientation_filtered.data[6]));
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(0).orientation_filtered.data[7]));
            Assert::AreEqual(0.0, process_context.data_rows.at(0).orientation_filtered.data[8]);

            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(1).orientation_filtered.data[0]));
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(1).orientation_filtered.data[1]));
            Assert::AreEqual(0.0, process_context.data_rows.at(1).orientation_filtered.data[2]);
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(1).orientation_filtered.data[3]));
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(1).orientation_filtered.data[4]));
            Assert::AreEqual(0.0, process_context.data_rows.at(1).orientation_filtered.data[5]);
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(1).orientation_filtered.data[6]));
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(1).orientation_filtered.data[7]));
            Assert::AreEqual(0.0, process_context.data_rows.at(1).orientation_filtered.data[8]);

            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(2).orientation_filtered.data[0]));
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(2).orientation_filtered.data[1]));
            Assert::AreEqual(0.0, process_context.data_rows.at(2).orientation_filtered.data[2]);
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(2).orientation_filtered.data[3]));
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(2).orientation_filtered.data[4]));
            Assert::AreEqual(0.0, process_context.data_rows.at(2).orientation_filtered.data[5]);
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(2).orientation_filtered.data[6]));
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(2).orientation_filtered.data[7]));
            Assert::AreEqual(0.0, process_context.data_rows.at(2).orientation_filtered.data[8]);

            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(3).orientation_filtered.data[0]));
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(3).orientation_filtered.data[1]));
            Assert::AreEqual(0.0, process_context.data_rows.at(3).orientation_filtered.data[2]);
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(3).orientation_filtered.data[3]));
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(3).orientation_filtered.data[4]));
            Assert::AreEqual(0.0, process_context.data_rows.at(3).orientation_filtered.data[5]);
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(3).orientation_filtered.data[6]));
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(3).orientation_filtered.data[7]));
            Assert::AreEqual(0.0, process_context.data_rows.at(3).orientation_filtered.data[8]);

            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(4).orientation_filtered.data[0]));
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(4).orientation_filtered.data[1]));
            Assert::AreEqual(0.0, process_context.data_rows.at(4).orientation_filtered.data[2]);
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(4).orientation_filtered.data[3]));
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(4).orientation_filtered.data[4]));
            Assert::AreEqual(0.0, process_context.data_rows.at(4).orientation_filtered.data[5]);
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(4).orientation_filtered.data[6]));
            Assert::IsTrue(float_compare(0.57735, process_context.data_rows.at(4).orientation_filtered.data[7]));
            Assert::AreEqual(0.0, process_context.data_rows.at(4).orientation_filtered.data[8]);

            // no error occured
            Assert::AreEqual(kuka_generator::NO_ERROR_RESULT, result);
        }

    };
}
