#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

#include <StringToDataRowConverter.h>
#include <float_math.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StringToDataRowConverterTest
{

    void data_row_has_default_values(kuka_generator::DataRow& data_row)
    {
        Assert::AreEqual(-1, data_row.index);

        Assert::AreEqual(0L, data_row.timestamp);

        Assert::AreEqual(0.0, data_row.position.x);
        Assert::AreEqual(0.0, data_row.position.y);
        Assert::AreEqual(0.0, data_row.position.z);

        Assert::AreEqual(0.0, data_row.position_filtered.x);
        Assert::AreEqual(0.0, data_row.position_filtered.y);
        Assert::AreEqual(0.0, data_row.position_filtered.z);

        Assert::AreEqual(1.0, data_row.orientation.data[0]);
        Assert::AreEqual(0.0, data_row.orientation.data[1]);
        Assert::AreEqual(0.0, data_row.orientation.data[2]);

        Assert::AreEqual(0.0, data_row.orientation.data[3]);
        Assert::AreEqual(1.0, data_row.orientation.data[4]);
        Assert::AreEqual(0.0, data_row.orientation.data[5]);

        Assert::AreEqual(0.0, data_row.orientation.data[6]);
        Assert::AreEqual(0.0, data_row.orientation.data[7]);
        Assert::AreEqual(1.0, data_row.orientation.data[8]);

        Assert::AreEqual(1.0, data_row.orientation_filtered.data[0]);
        Assert::AreEqual(0.0, data_row.orientation_filtered.data[1]);
        Assert::AreEqual(0.0, data_row.orientation_filtered.data[2]);

        Assert::AreEqual(0.0, data_row.orientation_filtered.data[3]);
        Assert::AreEqual(1.0, data_row.orientation_filtered.data[4]);
        Assert::AreEqual(0.0, data_row.orientation_filtered.data[5]);

        Assert::AreEqual(0.0, data_row.orientation_filtered.data[6]);
        Assert::AreEqual(0.0, data_row.orientation_filtered.data[7]);
        Assert::AreEqual(1.0, data_row.orientation_filtered.data[8]);

        Assert::AreEqual(0.0, data_row.velocity);

        Assert::IsTrue(data_row.alive);

        Assert::AreEqual(0.0, data_row.euler_angles.x);
        Assert::AreEqual(0.0, data_row.euler_angles.y);
        Assert::AreEqual(0.0, data_row.euler_angles.z);
    }

    /// <summary>
    /// https://learn.microsoft.com/de-de/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2022#general_is_True
    /// </summary>
    TEST_CLASS(StringToDataRowConverterTest)
    {

    public:

        TEST_METHOD(EmptyInput_NoCrash_Test)
        {
            // Arrange

            std::string data = "";
            kuka_generator::DataRow data_row;
            kuka_generator::StringToDataRowConverter string_to_data_row_converter;

            // Act

            string_to_data_row_converter.convert(data, data_row);

            // Assert

            data_row_has_default_values(data_row);

        }

        TEST_METHOD(WhiteSpaceInput_NoCrash_Test)
        {
            // Arrange

            std::string data = "     ";
            kuka_generator::DataRow data_row;
            kuka_generator::StringToDataRowConverter string_to_data_row_converter;

            // Act

            string_to_data_row_converter.convert(data, data_row);

            // Assert

            data_row_has_default_values(data_row);

        }

        TEST_METHOD(ValidInput_NoCrash_Test)
        {
            // Arrange

            std::string data = "13261.420898 1021.710788 -547.198540 632.801115 -0.130535 -0.984082 0.120599 -0.977709 0.147948 0.148988 -0.164459 -0.098463 -0.981457";
            kuka_generator::DataRow data_row;
            kuka_generator::StringToDataRowConverter string_to_data_row_converter;

            // Act

            string_to_data_row_converter.convert(data, data_row);

            // Assert

            Assert::AreEqual(-1, data_row.index);

            Assert::AreEqual(13261L, data_row.timestamp);

            Assert::IsTrue(float_compare(1021.71f, data_row.position.x, 1.0e-02));
            Assert::IsTrue(float_compare(-547.19f, data_row.position.y, 1.0e-02));
            Assert::IsTrue(float_compare(632.80f, data_row.position.z, 1.0e-02));

            Assert::AreEqual(0.0, data_row.position_filtered.x);
            Assert::AreEqual(0.0, data_row.position_filtered.y);
            Assert::AreEqual(0.0, data_row.position_filtered.z);

            Assert::IsTrue(float_compare(-0.13f, data_row.orientation.data[0], 1.0e-02));
            Assert::IsTrue(float_compare(-0.98f, data_row.orientation.data[1], 1.0e-02));
            Assert::IsTrue(float_compare(0.12f, data_row.orientation.data[2], 1.0e-02));

            Assert::IsTrue(float_compare(-0.97f, data_row.orientation.data[3], 1.0e-02));
            Assert::IsTrue(float_compare(0.14f, data_row.orientation.data[4], 1.0e-02));
            Assert::IsTrue(float_compare(0.14f, data_row.orientation.data[5], 1.0e-02));

            Assert::IsTrue(float_compare(-0.16f, data_row.orientation.data[6], 1.0e-02));
            Assert::IsTrue(float_compare(-0.09f, data_row.orientation.data[7], 1.0e-02));
            Assert::IsTrue(float_compare(-0.98f, data_row.orientation.data[8], 1.0e-02));

            Assert::AreEqual(1.0, data_row.orientation_filtered.data[0]);
            Assert::AreEqual(0.0, data_row.orientation_filtered.data[1]);
            Assert::AreEqual(0.0, data_row.orientation_filtered.data[2]);

            Assert::AreEqual(0.0, data_row.orientation_filtered.data[3]);
            Assert::AreEqual(1.0, data_row.orientation_filtered.data[4]);
            Assert::AreEqual(0.0, data_row.orientation_filtered.data[5]);

            Assert::AreEqual(0.0, data_row.orientation_filtered.data[6]);
            Assert::AreEqual(0.0, data_row.orientation_filtered.data[7]);
            Assert::AreEqual(1.0, data_row.orientation_filtered.data[8]);

            Assert::AreEqual(0.0, data_row.velocity);

            Assert::IsTrue(data_row.alive);

            Assert::AreEqual(0.0, data_row.euler_angles.x);
            Assert::AreEqual(0.0, data_row.euler_angles.y);
            Assert::AreEqual(0.0, data_row.euler_angles.z);

        }

    };
}
