#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>

struct PlayerData {
    std::string name;
    int health = 100;
    std::vector<std::string> skills;
    std::string position;
};

struct WorldData {
    std::string location;
    std::string time; // e.g., "day", "night"
};

namespace SaveManager {

    inline void savePlayerData(const PlayerData& player, const std::string& filename = "save.txt") {
        std::ofstream out(filename);
        if (!out) return;

        out << "# RPG Save File v1\n";
        out << "[Player]\n";
        out << "name=" << player.name << "\n";
        out << "health=" << player.health << "\n";
        out << "skills=";
        for (size_t i = 0; i < player.skills.size(); ++i) {
            out << player.skills[i];
            if (i < player.skills.size() - 1) out << ",";
        }
        out << "\n";
        out << "position=" << player.position << "\n";
    }

    inline PlayerData loadPlayerData(const std::string& filename = "save.txt") {
        PlayerData player;
        std::ifstream in(filename);
        if (!in) return player;

        std::string line;
        while (std::getline(in, line)) {
            if (line.empty() || line[0] == '#' || line[0] == '[') continue;

            auto sep = line.find('=');
            if (sep == std::string::npos) continue;

            std::string key = line.substr(0, sep);
            std::string value = line.substr(sep + 1);

            if (key == "name") player.name = value;
            else if (key == "health") player.health = std::stoi(value);
            else if (key == "skills") {
                std::stringstream ss(value);
                std::string skill;
                player.skills.clear();
                while (std::getline(ss, skill, ',')) {
                    player.skills.push_back(skill);
                }
            }
            else if (key == "position") player.position = value;
        }

        return player;
    }

    inline void saveWorldData(const WorldData& world, const std::string& filename = "world.txt") {
        std::ofstream out(filename);
        if (!out) return;

        out << "# World Save File v1\n";
        out << "[World]\n";
        out << "location=" << world.location << "\n";
        out << "time=" << world.time << "\n";
    }

    inline WorldData loadWorldData(const std::string& filename = "world.txt") {
        WorldData world;
        std::ifstream in(filename);
        if (!in) return world;

        std::string line;
        while (std::getline(in, line)) {
            if (line.empty() || line[0] == '#' || line[0] == '[') continue;

            auto sep = line.find('=');
            if (sep == std::string::npos) continue;

            std::string key = line.substr(0, sep);
            std::string value = line.substr(sep + 1);

            if (key == "location") world.location = value;
            else if (key == "time") world.time = value;
        }

        return world;
    }

    inline void createSaveDirectory(const std::string& dir) {
        std::filesystem::create_directories(dir);
    }

    inline void saveGame(const PlayerData& player, const WorldData& world, const std::string& saveName = "save") {
        std::string path = "saves/" + saveName + "/";
        createSaveDirectory(path);
        savePlayerData(player, path + "player.dat");
        saveWorldData(world, path + "world.dat");
    }

    inline void loadGame(PlayerData& player, WorldData& world, const std::string& saveName = "save") {
        std::string path = "saves/" + saveName + "/";
        player = loadPlayerData(path + "player.dat");
        world = loadWorldData(path + "world.dat");
    }
}