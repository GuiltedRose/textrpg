#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

class SaveSystem {
public:
    static void saveGame(const std::unordered_map<std::string, std::string>& playerData, const std::string& filename = "save.txt") {
        std::ofstream file(filename);
        if (!file) {
            std::cerr << "Error: Could not open file for saving.\n";
            return;
        }

        for (const auto& [key, value] : playerData) {
            file << key << "=" << value << "\n";
        }

        file.close();
        std::cout << "Game saved to " << filename << "!\n";
    }

    static void loadGame(std::unordered_map<std::string, std::string>& playerData, const std::string& filename = "save.txt") {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error: Could not open file for loading.\n";
            return;
        }

        playerData.clear();
        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find('=');
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                playerData[key] = value;
            }
        }

        file.close();
        std::cout << "Game loaded from " << filename << "!\n";
    }
};