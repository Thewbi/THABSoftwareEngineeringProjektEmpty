#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>

#include <velocity.h>
#include <Vector3d.h>
#include <double_math.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VelocityTest
{
    constexpr double epsilon = 0.0001;

    /// <summary>
    /// https://learn.microsoft.com/de-de/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2022#general_is_True
    /// </summary>
    TEST_CLASS(VelocityTest)
    {
    private:

        void add_point(std::vector<kuka_generator::DataRow>& data_rows, float x, float y, float z, double timestamp)
        {
            kuka_generator::DataRow data_row;
            data_row.position_filtered.set_values(x, y, z);
            data_row.timestamp = timestamp;
            data_rows.push_back(data_row);
        }

    public:

        TEST_METHOD(HappyCase_CorrectVelocity_Test)
        {
            // Arrange

            kuka_generator::Cvelo c_velo;

            std::vector<kuka_generator::DataRow> data_rows;
            add_point(data_rows, 1021.710788f, 547.198540f, 632.801115f, 0.123000);
            add_point(data_rows, 1006.183343f, 48.474911f, 596.267169f, 2.489000);

            // Act

            // compute velocity from timestamp and locations stored in the data
            std::vector<kuka_generator::DataRow>::iterator lastItr = std::prev(data_rows.end());
            c_velo.getvelocity(data_rows, data_rows.begin(), lastItr);

            // Assert

            Assert::IsTrue(kuka_generator::double_compare(data_rows.at(0).velocity, 200.438758));
        }

        TEST_METHOD(DivideByZero_PreventCrash_UseDefaultValue_Test)
        {
            // Arrange

            kuka_generator::Cvelo c_velo;

            std::vector<kuka_generator::DataRow> data_rows;
            add_point(data_rows, 1021.710788f, 547.198540f, 632.801115f, 0.0);
            add_point(data_rows, 1021.710788f, 547.198540f, 632.801115f, 0.0);

            // Act

            // compute velocity from timestamp and locations stored in the data
            std::vector<kuka_generator::DataRow>::iterator lastItr = std::prev(data_rows.end());
            c_velo.getvelocity(data_rows, data_rows.begin(), lastItr);

            // Assert

            Assert::IsTrue(kuka_generator::double_compare(data_rows.at(0).velocity, 0.2));
        }
    };
}
