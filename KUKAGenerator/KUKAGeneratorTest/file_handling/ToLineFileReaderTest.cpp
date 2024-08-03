#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>

#include <ToLineFileReader.h>
#include <IToLineFileReaderCallback.h>
#include <TestToLineFileReaderCallback.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// https://stackoverflow.com/questions/25150708/how-to-get-the-projectdir-path-in-a-visual-studio-native-c-unit-testing-usi
#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)

namespace ToLineFileReaderTest
{

    /// <summary>
    /// https://learn.microsoft.com/de-de/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2022#general_is_True
    /// </summary>
    TEST_CLASS(ToLineFileReaderTest)
    {

    public:

        TEST_METHOD(NonexistantFile_NoCrash_Test)
        {
            // Arrange

            std::string path_to_file = "ThisFileDoesNotExist.txt";
            kuka_generator::TestToLineFileReaderCallback test_to_line_file_reader_callback;

            kuka_generator::ToLineFileReader to_line_file_reader(path_to_file, test_to_line_file_reader_callback);

            // Act

            int result = to_line_file_reader.process();

            // Assert

            Assert::AreEqual(-1, result);

        }

        TEST_METHOD(EmptyFile_NoCrash_Test)
        {
            // Arrange

            // https://stackoverflow.com/questions/25150708/how-to-get-the-projectdir-path-in-a-visual-studio-native-c-unit-testing-usi
            std::string s = EXPAND(UNITTESTPRJ);
            s.erase(0, 1); // erase the first quote
            s.erase(s.size() - 2); // erase the last quote and the dot
            std::string my_project_dir = s;

            std::string path_to_file = my_project_dir + "resources\\TestToLineFileReader_Empty.txt";
            kuka_generator::TestToLineFileReaderCallback test_to_line_file_reader_callback;

            kuka_generator::ToLineFileReader to_line_file_reader(path_to_file, test_to_line_file_reader_callback);

            // Act

            int result = to_line_file_reader.process();

            // Assert

            Assert::AreEqual(0, result);

        }

        TEST_METHOD(NormalFile_Test)
        {
            // Arrange

            // https://stackoverflow.com/questions/25150708/how-to-get-the-projectdir-path-in-a-visual-studio-native-c-unit-testing-usi
            std::string s = EXPAND(UNITTESTPRJ);
            s.erase(0, 1); // erase the first quote
            s.erase(s.size() - 2); // erase the last quote and the dot
            std::string my_project_dir = s;

            std::string path_to_file = my_project_dir + "resources\\TestToLineFileReader_Normal.txt";
            kuka_generator::TestToLineFileReaderCallback test_to_line_file_reader_callback;

            kuka_generator::ToLineFileReader to_line_file_reader(path_to_file, test_to_line_file_reader_callback);

            // Act

            int result = to_line_file_reader.process();

            // Assert

            Assert::AreEqual(0, result);

            std::string this_string("this");
            Assert::IsTrue(this_string.compare(test_to_line_file_reader_callback.data.at(0)) == 0);

            std::string is_string("is");
            Assert::IsTrue(is_string.compare(test_to_line_file_reader_callback.data.at(1)) == 0);

            std::string a_string("a");
            Assert::IsTrue(a_string.compare(test_to_line_file_reader_callback.data.at(2)) == 0);

            std::string test_string("test");
            Assert::IsTrue(test_string.compare(test_to_line_file_reader_callback.data.at(3)) == 0);

        }

    };
}
