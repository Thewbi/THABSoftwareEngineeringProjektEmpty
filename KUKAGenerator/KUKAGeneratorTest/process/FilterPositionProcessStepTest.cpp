#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

#include <FilterPositionProcessStep.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// https://stackoverflow.com/questions/25150708/how-to-get-the-projectdir-path-in-a-visual-studio-native-c-unit-testing-usi
#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)

namespace FilterPositionProcessStepTest
{

    /// <summary>
    /// https://learn.microsoft.com/de-de/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2022#general_is_True
    /// </summary>
    TEST_CLASS(FilterPositionProcessStepTest)
    {

    public:

        TEST_METHOD(Filter_Data_Empty_Test)
        {
            // Arrange

            kuka_generator::ProcessContext process_context;
            process_context.length_filter_position = 100;

            kuka_generator::FilterPositionProcessStep filter_position_process_step(process_context);

            // Act

            int result = filter_position_process_step.process();

            // Assert

            // no error occured
            Assert::AreEqual(kuka_generator::NO_ERROR_RESULT, result);
        }

        TEST_METHOD(FilterWindowLength_1_Test)
        {
            // Arrange

            kuka_generator::DataRow data_row;
            data_row.alive = true;
            data_row.position.x = 0.1;
            data_row.position.y = 0.2;
            data_row.position.z = 0.3;

            kuka_generator::ProcessContext process_context;
            process_context.data_rows.push_back(data_row);
            process_context.length_filter_position = 1;

            kuka_generator::FilterPositionProcessStep filter_position_process_step(process_context);

            // Act

            int result = filter_position_process_step.process();

            // Assert

            // the filtered value is the same as the original data since the window has a size of 1
            Assert::AreEqual(process_context.data_rows.at(0).position.x, process_context.data_rows.at(0).position_filtered.x);
            Assert::AreEqual(process_context.data_rows.at(0).position.y, process_context.data_rows.at(0).position_filtered.y);
            Assert::AreEqual(process_context.data_rows.at(0).position.z, process_context.data_rows.at(0).position_filtered.z);

            // no error occured
            Assert::AreEqual(kuka_generator::NO_ERROR_RESULT, result);
        }

        TEST_METHOD(FilterWindowLength_illegal_window_size_Test)
        {
            // Arrange

            kuka_generator::ProcessContext process_context;

            kuka_generator::DataRow data_row;
            data_row.alive = true;

            data_row.position.x = 1.0;
            data_row.position.y = 1.0;
            data_row.position.z = 1.0;
            process_context.data_rows.push_back(data_row);

            data_row.position.x = 2.0;
            data_row.position.y = 2.0;
            data_row.position.z = 2.0;
            process_context.data_rows.push_back(data_row);

            data_row.position.x = 3.0;
            data_row.position.y = 3.0;
            data_row.position.z = 3.0;
            process_context.data_rows.push_back(data_row);

            process_context.length_filter_position = -17;

            kuka_generator::FilterPositionProcessStep filter_position_process_step(process_context);

            // Act

            int result = filter_position_process_step.process();

            // Assert

            // the filtered value is the same as the original data since the window has a size of 1
            Assert::AreEqual(process_context.data_rows.at(0).position.x, process_context.data_rows.at(0).position_filtered.x);
            Assert::AreEqual(process_context.data_rows.at(0).position.y, process_context.data_rows.at(0).position_filtered.y);
            Assert::AreEqual(process_context.data_rows.at(0).position.z, process_context.data_rows.at(0).position_filtered.z);

            Assert::AreEqual(process_context.data_rows.at(1).position.x, process_context.data_rows.at(1).position_filtered.x);
            Assert::AreEqual(process_context.data_rows.at(1).position.y, process_context.data_rows.at(1).position_filtered.y);
            Assert::AreEqual(process_context.data_rows.at(1).position.z, process_context.data_rows.at(1).position_filtered.z);

            Assert::AreEqual(process_context.data_rows.at(2).position.x, process_context.data_rows.at(2).position_filtered.x);
            Assert::AreEqual(process_context.data_rows.at(2).position.y, process_context.data_rows.at(2).position_filtered.y);
            Assert::AreEqual(process_context.data_rows.at(2).position.z, process_context.data_rows.at(2).position_filtered.z);

            // no error occured
            Assert::AreEqual(kuka_generator::NO_ERROR_RESULT, result);
        }

        TEST_METHOD(FilterWindowLength_window_size_3_Test)
        {
            // Arrange

            kuka_generator::ProcessContext process_context;

            kuka_generator::DataRow data_row;
            data_row.alive = true;

            data_row.position.x = 1.0;
            data_row.position.y = 1.0;
            data_row.position.z = 1.0;
            process_context.data_rows.push_back(data_row);

            data_row.position.x = 2.0;
            data_row.position.y = 2.0;
            data_row.position.z = 2.0;
            process_context.data_rows.push_back(data_row);

            data_row.position.x = 3.0;
            data_row.position.y = 3.0;
            data_row.position.z = 3.0;
            process_context.data_rows.push_back(data_row);

            data_row.position.x = 4.0;
            data_row.position.y = 4.0;
            data_row.position.z = 4.0;
            process_context.data_rows.push_back(data_row);

            data_row.position.x = 5.0;
            data_row.position.y = 5.0;
            data_row.position.z = 5.0;
            process_context.data_rows.push_back(data_row);

            process_context.length_filter_position = 3;

            kuka_generator::FilterPositionProcessStep filter_position_process_step(process_context);

            // Act

            int result = filter_position_process_step.process();

            // Assert

            // the filtered value is the same as the original data since the window has a size of 1
            Assert::AreEqual(1.0, process_context.data_rows.at(0).position_filtered.x);
            Assert::AreEqual(1.0, process_context.data_rows.at(0).position_filtered.y);
            Assert::AreEqual(1.0, process_context.data_rows.at(0).position_filtered.z);

            Assert::AreEqual((1.0 + 2.0) / 2.0, process_context.data_rows.at(1).position_filtered.x);
            Assert::AreEqual((1.0 + 2.0) / 2.0, process_context.data_rows.at(1).position_filtered.y);
            Assert::AreEqual((1.0 + 2.0) / 2.0, process_context.data_rows.at(1).position_filtered.z);

            Assert::AreEqual((1.0 + 2.0 + 3.0) / 3.0, process_context.data_rows.at(2).position_filtered.x);
            Assert::AreEqual((1.0 + 2.0 + 3.0) / 3.0, process_context.data_rows.at(2).position_filtered.y);
            Assert::AreEqual((1.0 + 2.0 + 3.0) / 3.0, process_context.data_rows.at(2).position_filtered.z);

            Assert::AreEqual((2.0 + 3.0 + 4.0) / 3.0, process_context.data_rows.at(3).position_filtered.x);
            Assert::AreEqual((2.0 + 3.0 + 4.0) / 3.0, process_context.data_rows.at(3).position_filtered.y);
            Assert::AreEqual((2.0 + 3.0 + 4.0) / 3.0, process_context.data_rows.at(3).position_filtered.z);

            Assert::AreEqual((3.0 + 4.0 + 5.0) / 3.0, process_context.data_rows.at(4).position_filtered.x);
            Assert::AreEqual((3.0 + 4.0 + 5.0) / 3.0, process_context.data_rows.at(4).position_filtered.y);
            Assert::AreEqual((3.0 + 4.0 + 5.0) / 3.0, process_context.data_rows.at(4).position_filtered.z);

            // no error occured
            Assert::AreEqual(kuka_generator::NO_ERROR_RESULT, result);
        }

        TEST_METHOD(FilterWindowLength_Larger_Than_Data_Test)
        {
            // Arrange

            kuka_generator::ProcessContext process_context;

            kuka_generator::DataRow data_row;
            data_row.alive = true;

            data_row.position.x = 1.0;
            data_row.position.y = 1.0;
            data_row.position.z = 1.0;
            process_context.data_rows.push_back(data_row);

            data_row.position.x = 2.0;
            data_row.position.y = 2.0;
            data_row.position.z = 2.0;
            process_context.data_rows.push_back(data_row);

            data_row.position.x = 3.0;
            data_row.position.y = 3.0;
            data_row.position.z = 3.0;
            process_context.data_rows.push_back(data_row);

            data_row.position.x = 4.0;
            data_row.position.y = 4.0;
            data_row.position.z = 4.0;
            process_context.data_rows.push_back(data_row);

            data_row.position.x = 5.0;
            data_row.position.y = 5.0;
            data_row.position.z = 5.0;
            process_context.data_rows.push_back(data_row);

            process_context.length_filter_position = 3000;

            kuka_generator::FilterPositionProcessStep filter_position_process_step(process_context);

            // Act

            int result = filter_position_process_step.process();

            // Assert

            // the filtered value is the same as the original data since the window has a size of 1
            Assert::AreEqual(1.0, process_context.data_rows.at(0).position_filtered.x);
            Assert::AreEqual(1.0, process_context.data_rows.at(0).position_filtered.y);
            Assert::AreEqual(1.0, process_context.data_rows.at(0).position_filtered.z);

            Assert::AreEqual((1.0 + 2.0) / 2.0, process_context.data_rows.at(1).position_filtered.x);
            Assert::AreEqual((1.0 + 2.0) / 2.0, process_context.data_rows.at(1).position_filtered.y);
            Assert::AreEqual((1.0 + 2.0) / 2.0, process_context.data_rows.at(1).position_filtered.z);

            Assert::AreEqual((1.0 + 2.0 + 3.0) / 3.0, process_context.data_rows.at(2).position_filtered.x);
            Assert::AreEqual((1.0 + 2.0 + 3.0) / 3.0, process_context.data_rows.at(2).position_filtered.y);
            Assert::AreEqual((1.0 + 2.0 + 3.0) / 3.0, process_context.data_rows.at(2).position_filtered.z);

            Assert::AreEqual((1.0 + 2.0 + 3.0 + 4.0) / 4.0, process_context.data_rows.at(3).position_filtered.x);
            Assert::AreEqual((1.0 + 2.0 + 3.0 + 4.0) / 4.0, process_context.data_rows.at(3).position_filtered.y);
            Assert::AreEqual((1.0 + 2.0 + 3.0 + 4.0) / 4.0, process_context.data_rows.at(3).position_filtered.z);

            Assert::AreEqual((1.0 + 2.0 + 3.0 + 4.0 + 5.0) / 5.0, process_context.data_rows.at(4).position_filtered.x);
            Assert::AreEqual((1.0 + 2.0 + 3.0 + 4.0 + 5.0) / 5.0, process_context.data_rows.at(4).position_filtered.y);
            Assert::AreEqual((1.0 + 2.0 + 3.0 + 4.0 + 5.0) / 5.0, process_context.data_rows.at(4).position_filtered.z);

            // no error occured
            Assert::AreEqual(kuka_generator::NO_ERROR_RESULT, result);
        }

    };
}
