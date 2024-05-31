#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>

#include <Line3D.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Line3DTest
{
    constexpr double epsilon = 0.0001;

    TEST_CLASS(Line3DTest)
    {
    public:

        TEST_METHOD(CreateLineFromPointsTest)
        {
            // Arrange

            // these points are used to create a line
            kuka_generator::Vector3f start(1.0f, 2.0f, 3.0f);
            kuka_generator::Vector3f end(2.0f, 2.0f, 3.0f);

            // create a line from the points
            kuka_generator::CLine3D line3D(start, end);

            // Act

            // Assert

            // check that the points have been stored inside the line
            Assert::AreEqual(1.0f, line3D.p1.x);
            Assert::AreEqual(2.0f, line3D.p1.y);
            Assert::AreEqual(3.0f, line3D.p1.z);

            Assert::AreEqual(2.0f, line3D.p2.x);
            Assert::AreEqual(2.0f, line3D.p2.y);
            Assert::AreEqual(3.0f, line3D.p2.z);
        }

        TEST_METHOD(DistanceToPointOnLineIsZeroTest)
        {
            // Arrange

            // these points are used to create a line
            kuka_generator::Vector3f start(1.0f, 2.0f, 3.0f);
            kuka_generator::Vector3f end(2.0f, 2.0f, 3.0f);

            // create a line from the points
            kuka_generator::CLine3D line3D(start, end);

            // Act

            double distance = line3D.distanceTo(start);

            // Assert

            // distance to is near zero
            Assert::IsTrue(distance < epsilon);
        }

        TEST_METHOD(DistanceToPointTest)
        {
            // Arrange

            // these points are used to create a line
            kuka_generator::Vector3f start(1.0f, 0.0f, 0.0f);
            kuka_generator::Vector3f end(2.0f, 0.0f, 0.0f);

            // create a line from the points
            kuka_generator::CLine3D line3D(start, end);

            // create test point
            kuka_generator::Vector3f test_point(1.0f, 1.0f, 0.0f);

            // Act

            double distance = line3D.distanceTo(test_point);

            // Assert

            // distance to line is 1.0
            Assert::AreEqual(1.0, distance);
        }
    };
}
