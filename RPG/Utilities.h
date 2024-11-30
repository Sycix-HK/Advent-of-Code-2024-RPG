#pragma once

#include "Core.h"

#include <fstream>

namespace ReadIntents
{
    std::vector<std::string> ReadAsStrings(const std::string& filePath) 
    {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }

        file.close();
        return lines;
    }

    std::vector<int> ReadAsInts(const std::string& filePath) 
    {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        std::vector<int> numbers;
        std::string line;
        while (std::getline(file, line)) {
            try {
                numbers.push_back(std::stoi(line));
            } catch (const std::invalid_argument& e) {
                throw std::runtime_error("Invalid integer in file: " + line);
            } catch (const std::out_of_range& e) {
                throw std::runtime_error("Integer out of range in file: " + line);
            }
        }

        file.close();
        return numbers;
    }
}

namespace SystemUtilities 
{
    static void flavorPrint(std::string text)
    {
        std::cout << "\x1b[0m * " << text << "\x1b[97m\n";
    }

    static void printState(GameState *apState)
    {
        std::cout << std::endl
                  << "\x1b[97m- Age: \x1b[95m" << apState->age << "\x1b[97m years" <<  std::endl
                  << "\x1b[97m- Mana: \x1b[94m" << g_manaCounter << "\x1b[97m / \x1b[34m" << apState->maxMana() << std::endl
                  << "\x1b[97m- Amulet Wear: \x1b[33m" << apState->amuletWear << "\x1b[97m lines"  << std::endl
                  << "\x1b[0m- Characters broken out of amulet: \x1b[97m"<< apState->brokenCharacters << std::endl
                  << "\x1b[0m" << std::endl;
    }
}