#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>

#include <DP.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DPTest
{
    constexpr double epsilon = 0.0001;

    /// <summary>
    /// https://learn.microsoft.com/de-de/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2022#general_is_True
    /// </summary>
    TEST_CLASS(DPTest)
    {
    private:

        void add_point(std::vector<kuka_generator::DataRow>& data_rows, float x, float y, float z)
        {
            kuka_generator::DataRow data_row;
            data_row.position_filtered.set_values(x, y, z);
            data_rows.push_back(data_row);
        }

    public:

        TEST_METHOD(NoPoints_NoCrash_Test)
        {
            // Arrange

            std::vector<kuka_generator::DataRow> data_rows;

            double max_distance = 5.0;
            kuka_generator::CDP DP;

            // Act

            DP.DPRecursive(data_rows, data_rows.begin(), data_rows.end(), max_distance);

            // Assert

            // no points have been added
            Assert::IsTrue(data_rows.size() == 0);

        }

        TEST_METHOD(SinglePoint_NoCrash_Test)
        {
            // Arrange

            std::vector<kuka_generator::DataRow> data_rows;
            add_point(data_rows, 1.0f, 2.0f, 3.0f);

            double max_distance = 5.0;
            kuka_generator::CDP DP;

            // Act

            DP.DPRecursive(data_rows, data_rows.begin(), data_rows.end(), max_distance);

            // Assert

            // no points have been added
            Assert::IsTrue(data_rows.size() == 1);

            // all points are alive, not points have been removed
            for (kuka_generator::DataRow& data_row : data_rows)
            {
                Assert::IsTrue(data_row.alive);
            }

        }

        TEST_METHOD(TwoPoints_KeepBothPoints_Test)
        {
            // Arrange

            std::vector<kuka_generator::DataRow> data_rows;
            add_point(data_rows, 1.0f, 2.0f, 3.0f);
            add_point(data_rows, 2.0f, 2.0f, 3.0f);

            double max_distance = 5.0;
            kuka_generator::CDP DP;

            // Act

            DP.DPRecursive(data_rows, data_rows.begin(), std::prev(data_rows.end()), max_distance);

            // Assert

            // all points are alive, not points have been removed
            for (kuka_generator::DataRow& data_row : data_rows)
            {
                Assert::IsTrue(data_row.alive);
            }
        }

        TEST_METHOD(FurthestPointWithinMaxDistance_OnlyStartAndEndRemain_Test)
        {
            // Arrange

            std::vector<kuka_generator::DataRow> data_rows;
            add_point(data_rows, 1.0f, 2.0f, 3.0f);
            add_point(data_rows, 2.0f, 2.0f, 3.0f);
            add_point(data_rows, 3.0f, 2.0f, 3.0f);
            add_point(data_rows, 4.0f, 2.0f, 3.0f);
            add_point(data_rows, 5.0f, 2.0f, 3.0f);

            double max_distance = 5.0;
            kuka_generator::CDP DP;

            // Act

            DP.DPRecursive(data_rows, data_rows.begin(), std::prev(data_rows.end()), max_distance);

            // Assert

            // only the start and end points survive
            Assert::IsTrue(data_rows.at(0).alive); // alive
            Assert::IsFalse(data_rows.at(1).alive);
            Assert::IsFalse(data_rows.at(2).alive);
            Assert::IsFalse(data_rows.at(3).alive);
            Assert::IsTrue(data_rows.at(4).alive); // alive
        }

        TEST_METHOD(TestSet_Test)
        {
            // Arrange

            std::vector<kuka_generator::DataRow> data_rows;
            add_point(data_rows, 1.0f, 2.0f, 3.0f);
            add_point(data_rows, 2.0f, 2.0f, 3.0f);
            add_point(data_rows, 3.0f, 2.0f, 3.0f);
            add_point(data_rows, 3.0f, 15.0f, 3.0f);
            add_point(data_rows, 13.0f, 20.0f, 3.0f);
            add_point(data_rows, 16.0f, 20.0f, 3.0f);
            add_point(data_rows, 20.0f, 20.0f, 3.0f);

            double max_distance = 5.0;
            kuka_generator::CDP DP;

            // Act

            DP.DPRecursive(data_rows, data_rows.begin(), std::prev(data_rows.end()), max_distance);

            // Assert

            // a max distance point has been found
            // There has been a single recursion
            // The insignificant points have been removed
            Assert::IsTrue(data_rows.at(0).alive); // alive
            Assert::IsFalse(data_rows.at(1).alive);
            Assert::IsFalse(data_rows.at(2).alive);
            Assert::IsTrue(data_rows.at(3).alive); // alive
            Assert::IsFalse(data_rows.at(4).alive);
            Assert::IsFalse(data_rows.at(5).alive);
            Assert::IsTrue(data_rows.at(6).alive); // alive
        }
    };
}
