#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace KUKAGeneratorTest
{
    TEST_CLASS(KUKAGeneratorTest)
    {
    public:

        TEST_METHOD(TestMethod1)
        {
            std::string expected = "Hello World!\n";
            std::string actual = "Hello World!\n";



            // Test
            Assert::AreEqual(expected, actual);
        }
    };
}
