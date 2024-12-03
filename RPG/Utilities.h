#pragma once

#include "Core.h"

#include <fstream>
#include <sstream>
#include <filesystem>

namespace AOCUtilities
{
    std::vector<std::string> ReadLines(int aRoom)
    {
        std::stringstream path_ss;
        path_ss << "X:/AdventOfCode/Advent-of-Code-2024-RPG/Dungeon/Room"<<aRoom<<"/input.txt";
        std::string filePath = path_ss.str();

        std::ifstream file(filePath);
        if (!file.is_open())
        {
            std::stringstream path_ss;
            path_ss << "X:/AdventOfCode/Advent-of-Code-2024-RPG/Dungeon/Room" << aRoom << "/input.txt";
            std::string filePath = path_ss.str();
            if (!file.is_open())
            {
                theme->MissingInput();
                throw std::runtime_error("Failed to open file: " + filePath);
            }
        }

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line))
        {
            lines.push_back(line);
        }

        file.close();
        return lines;
    }

    std::vector<std::string> split(const std::string &str, const std::string &delimiter)
    {
        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end = str.find(delimiter);

        while (end != std::string::npos)
        {
            tokens.push_back(str.substr(start, end - start));
            start = end + delimiter.length();
            end = str.find(delimiter, start);
        }

        tokens.push_back(str.substr(start));

        return tokens;
    }
}
