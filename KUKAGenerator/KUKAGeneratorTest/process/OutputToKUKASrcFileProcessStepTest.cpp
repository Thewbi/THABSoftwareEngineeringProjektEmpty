#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

#include <OutputToKUKASrcFileProcessStep.h>
#include <IOutputToFileCallback.h>
#include <TestOutputToFileCallback.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// https://stackoverflow.com/questions/25150708/how-to-get-the-projectdir-path-in-a-visual-studio-native-c-unit-testing-usi
#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)

namespace OutputToKUKASrcFileProcessStepTest
{

    /// <summary>
    /// https://learn.microsoft.com/de-de/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2022#general_is_True
    /// </summary>
    TEST_CLASS(OutputToKUKASrcFileProcessStepTest)
    {

    public:

        TEST_METHOD(HappyCase_Test)
        {
            // Arrange

            kuka_generator::DataRow data_row;
            data_row.alive = true;
            data_row.velocity = 1.234;
            data_row.position_filtered.x = 0.1;
            data_row.position_filtered.y = 0.2;
            data_row.position_filtered.z = 0.3;
            data_row.euler_angles.x = 1.0;
            data_row.euler_angles.y = 2.0;
            data_row.euler_angles.z = 3.0;

            kuka_generator::ProcessContext process_context;
            process_context.output_file = "testfolder/testfilename";
            process_context.data_rows.push_back(data_row);

            kuka_generator::TestOutputToFileCallback test_output_to_file_callback;

            kuka_generator::OutputToKUKASrcFileProcessStep output_to_KUKA_src_file_process_step(process_context, test_output_to_file_callback);

            // Act

            int result = output_to_KUKA_src_file_process_step.process();

            // Assert

            // no error occured
            Assert::AreEqual(kuka_generator::NO_ERROR_RESULT, result);

            // the folders have been created
            Assert::IsTrue(test_output_to_file_callback.filepath.compare("testfolder/testfilename") == 0);

            // the file has been closed
            Assert::IsTrue(test_output_to_file_callback.close_file_called);

            Assert::IsTrue(test_output_to_file_callback.data.at(0).compare("DEF testfolder/testfilename\n") == 0);
            Assert::IsTrue(test_output_to_file_callback.data.at(1).compare("PTP $POS_ACT\n") == 0);
            Assert::IsTrue(test_output_to_file_callback.data.at(2).compare("$VEL.CP=1.234000\n") == 0);
            Assert::IsTrue(test_output_to_file_callback.data.at(3).compare("LIN {X 0.100000, Y 0.200000, Z 0.300000, A 1.000000, B 2.000000, C 3.000000} \n") == 0);
            Assert::IsTrue(test_output_to_file_callback.data.at(4).compare("$VEL.CP=0.000000\n") == 0);
            Assert::IsTrue(test_output_to_file_callback.data.at(5).compare("END") == 0);

        }

        TEST_METHOD(NoData_Test)
        {
            // Arrange

            kuka_generator::ProcessContext process_context;
            process_context.output_file = "testfolder/testfilename";

            kuka_generator::TestOutputToFileCallback test_output_to_file_callback;

            kuka_generator::OutputToKUKASrcFileProcessStep output_to_KUKA_src_file_process_step(process_context, test_output_to_file_callback);

            // Act

            int result = output_to_KUKA_src_file_process_step.process();

            // Assert

            // error occured
            Assert::AreEqual(-1, result);

        }

        TEST_METHOD(No_OutputFile_Test)
        {
            // Arrange

            kuka_generator::DataRow data_row;
            data_row.alive = true;
            data_row.velocity = 1.234;
            data_row.position_filtered.x = 0.1;
            data_row.position_filtered.y = 0.2;
            data_row.position_filtered.z = 0.3;
            data_row.euler_angles.x = 1.0;
            data_row.euler_angles.y = 2.0;
            data_row.euler_angles.z = 3.0;

            kuka_generator::ProcessContext process_context;
            process_context.data_rows.push_back(data_row);

            kuka_generator::TestOutputToFileCallback test_output_to_file_callback;

            kuka_generator::OutputToKUKASrcFileProcessStep output_to_KUKA_src_file_process_step(process_context, test_output_to_file_callback);

            // Act

            int result = output_to_KUKA_src_file_process_step.process();

            // Assert

            // no error occured
            Assert::AreEqual(-2, result);

        }

        TEST_METHOD(Dead_Rows_Are_Skipped_Test)
        {
            // Arrange

            kuka_generator::ProcessContext process_context;
            process_context.output_file = "testfolder/testfilename";

            kuka_generator::DataRow data_row;
            data_row.alive = true;
            data_row.velocity = 1.234;
            data_row.position_filtered.x = 0.1;
            data_row.position_filtered.y = 0.2;
            data_row.position_filtered.z = 0.3;
            data_row.euler_angles.x = 1.0;
            data_row.euler_angles.y = 2.0;
            data_row.euler_angles.z = 3.0;

            process_context.data_rows.push_back(data_row);

            data_row.alive = false;
            data_row.velocity = 1.234;
            data_row.position_filtered.x = 0.1;
            data_row.position_filtered.y = 0.2;
            data_row.position_filtered.z = 0.3;
            data_row.euler_angles.x = 1.0;
            data_row.euler_angles.y = 2.0;
            data_row.euler_angles.z = 3.0;

            process_context.data_rows.push_back(data_row);

            kuka_generator::TestOutputToFileCallback test_output_to_file_callback;

            kuka_generator::OutputToKUKASrcFileProcessStep output_to_KUKA_src_file_process_step(process_context, test_output_to_file_callback);

            // Act

            int result = output_to_KUKA_src_file_process_step.process();

            // Assert

            // no error occured
            Assert::AreEqual(kuka_generator::NO_ERROR_RESULT, result);

            // the folders have been created
            Assert::IsTrue(test_output_to_file_callback.filepath.compare("testfolder/testfilename") == 0);

            // the file has been closed
            Assert::IsTrue(test_output_to_file_callback.close_file_called);

            Assert::IsTrue(test_output_to_file_callback.data.at(0).compare("DEF testfolder/testfilename\n") == 0);
            Assert::IsTrue(test_output_to_file_callback.data.at(1).compare("PTP $POS_ACT\n") == 0);
            Assert::IsTrue(test_output_to_file_callback.data.at(2).compare("$VEL.CP=1.234000\n") == 0);
            Assert::IsTrue(test_output_to_file_callback.data.at(3).compare("LIN {X 0.100000, Y 0.200000, Z 0.300000, A 1.000000, B 2.000000, C 3.000000} \n") == 0);
            Assert::IsTrue(test_output_to_file_callback.data.at(4).compare("$VEL.CP=0.000000\n") == 0);
            Assert::IsTrue(test_output_to_file_callback.data.at(5).compare("END") == 0);

        }

    };
}
