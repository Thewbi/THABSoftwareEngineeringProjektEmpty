#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>

#include <Vector3d.h>
#include <double_math.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Vector3DTest
{
    constexpr double epsilon = 0.0001;

    /// <summary>
    /// https://learn.microsoft.com/de-de/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2022#general_is_True
    /// </summary>
    TEST_CLASS(Vector3DTest)
    {
    public:

        TEST_METHOD(DefaultConstructor_ZeroVector_Test)
        {
            // Arrange

            kuka_generator::Vector3d vector;

            // Act

            // Assert

            // the constructor creates the zero vector
            Assert::IsTrue(kuka_generator::double_compare(vector.x, 0.0));
            Assert::IsTrue(kuka_generator::double_compare(vector.y, 0.0));
            Assert::IsTrue(kuka_generator::double_compare(vector.z, 0.0));
        }

        TEST_METHOD(Constructor_CorrectVector_Test)
        {
            // Arrange

            kuka_generator::Vector3d vector(1.2, 3.4, 5.6);

            // Act

            // Assert

            // the constructor creates the zero vector
            Assert::IsTrue(kuka_generator::double_compare(vector.x, 1.2));
            Assert::IsTrue(kuka_generator::double_compare(vector.y, 3.4));
            Assert::IsTrue(kuka_generator::double_compare(vector.z, 5.6));
        }

        TEST_METHOD(SetValues_CorrectVector_Test)
        {
            // Arrange

            kuka_generator::Vector3d vector(1.2, 3.4, 5.6);

            // Act

            vector.set_values(6.5, 4.3, 2.1);

            // Assert

            Assert::IsTrue(kuka_generator::double_compare(vector.x, 6.5));
            Assert::IsTrue(kuka_generator::double_compare(vector.y, 4.3));
            Assert::IsTrue(kuka_generator::double_compare(vector.z, 2.1));
        }

        TEST_METHOD(Distance_CorrectResult_Test)
        {
            // Arrange

            kuka_generator::Vector3d vectorA(0.0, 0.0, 0.0);
            kuka_generator::Vector3d vectorB(1.0, 0.0, 0.0);

            // Act

            double result = vectorA.distanceTo(vectorB);

            // Assert

            Assert::IsTrue(kuka_generator::double_compare(result, 1.0));
        }

        TEST_METHOD(ZeroVectorDistance_CorrectResult_Test)
        {
            // Arrange

            kuka_generator::Vector3d vectorA(0.0, 0.0, 0.0);
            kuka_generator::Vector3d vectorB(0.0, 0.0, 0.0);

            // Act

            double result = vectorA.distanceTo(vectorB);

            // Assert

            // the constructor creates the zero vector
            Assert::IsTrue(kuka_generator::double_compare(result, 0.0));
        }

        TEST_METHOD(NormalizeVector_CorrectResult_Test)
        {
            // Arrange

            kuka_generator::Vector3d vector(17.0, 17.0, 17.0);

            // Act

            vector.normalize();

            // Assert

            Assert::IsTrue(kuka_generator::double_compare(vector.x, 0.57735));
            Assert::IsTrue(kuka_generator::double_compare(vector.y, 0.57735));
            Assert::IsTrue(kuka_generator::double_compare(vector.z, 0.57735));
        }

        TEST_METHOD(CrossProduct_CorrectResult_Test)
        {
            // Arrange

            kuka_generator::Vector3d vectorA(1.0, 0.0, 0.0);
            kuka_generator::Vector3d vectorB(0.0, 1.0, 0.0);

            // Act

            kuka_generator::Vector3d vectorC = vectorA.cross_product(vectorB);

            // Assert

            Assert::IsTrue(kuka_generator::double_compare(vectorC.x, 0.0));
            Assert::IsTrue(kuka_generator::double_compare(vectorC.y, 0.0));
            Assert::IsTrue(kuka_generator::double_compare(vectorC.z, 1.0));
        }
    };
}
