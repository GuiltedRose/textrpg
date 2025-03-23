#pragma once

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <filesystem>

struct PlayerData {
    std::string name;
    int health = 100;
    std::string position;

    std::map<std::string, int> skills;    // Skill name → level
    std::map<std::string, int> skillXP;   // Skill name → XP

    std::string inventory;
};

struct WorldData {
    std::string location;
    std::string time;
    unsigned int seed = 0;
};

namespace SaveManager {

    inline void savePlayerData(const PlayerData& player, const std::string& filename = "save.txt") {
        std::ofstream out(filename);
        if (!out) return;

        out << "# RPG Save File v2\n";
        out << "[Player]\n";
        out << "name=" << player.name << "\n";
        out << "health=" << player.health << "\n";
        out << "position=" << player.position << "\n";
        out << "inventory=" << player.inventory << "\n";

        // Save skills
        out << "skills=";
        bool first = true;
        for (const auto& [skill, level] : player.skills) {
            if (!first) out << ",";
            out << skill << ":" << level;
            first = false;
        }
        out << "\n";

        // Save skill XP
        out << "skill_xp=";
        first = true;
        for (const auto& [skill, xp] : player.skillXP) {
            if (!first) out << ",";
            out << skill << ":" << xp;
            first = false;
        }
        out << "\n";
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
            else if (key == "position") player.position = value;
            else if (key == "inventory") player.inventory = value;

            else if (key == "skills") {
                std::stringstream ss(value);
                std::string entry;
                while (std::getline(ss, entry, ',')) {
                    auto colon = entry.find(':');
                    if (colon != std::string::npos) {
                        std::string skill = entry.substr(0, colon);
                        int level = std::stoi(entry.substr(colon + 1));
                        player.skills[skill] = level;
                    }
                }
            }

            else if (key == "skill_xp") {
                std::stringstream ss(value);
                std::string entry;
                while (std::getline(ss, entry, ',')) {
                    auto colon = entry.find(':');
                    if (colon != std::string::npos) {
                        std::string skill = entry.substr(0, colon);
                        int xp = std::stoi(entry.substr(colon + 1));
                        player.skillXP[skill] = xp;
                    }
                }
            }
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
        out << "seed=" << world.seed << "\n";
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
            else if (key == "seed") world.seed = std::stoul(value);
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
