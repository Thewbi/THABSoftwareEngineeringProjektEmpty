#pragma once

#include <StringToDataRowConverter.h>

namespace kuka_generator
{
    bool isBlank(std::string data)
    {
        return !std::any_of(data.begin(), data.end(), [](unsigned char c) { return !std::isspace(c); });
    }

    void StringToDataRowConverter::convert(std::string line, DataRow& data_row)
    {
        // Format:
        // (t, X, Y, Z, R11..R33)

        // Example:
        // 28387.427734 1033.365021 -554.171979 632.421231 -0.088749 -0.980695 0.174243 -0.978993 0.118123 0.166192 -0.183566 -0.155834 -0.970577

        if (isBlank(line))
        {
            return;
        }

        std::istringstream istringstream(line);

        // timestamp
        std::string timestamp_as_string;
        istringstream >> timestamp_as_string;
        data_row.timestamp = stod(timestamp_as_string);

        // x
        std::string float_as_string;
        istringstream >> float_as_string;
        data_row.position.x = stod(float_as_string);

        // y
        istringstream >> float_as_string;
        data_row.position.y = stod(float_as_string);

        // z
        istringstream >> float_as_string;
        data_row.position.z = stod(float_as_string);

        for (int i = 0; i < 9; i++)
        {
            istringstream >> float_as_string;
            data_row.orientation[i] = stod(float_as_string);
        }
    }
}
