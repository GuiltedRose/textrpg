#pragma once

#include "MapTile.h"
#include "WorldGenerator.h"
#include "Player.h"
#include "gameobjects/Enemy.h"

#include <vector>
#include <string>
#include <unordered_map>

class World {
public:
    World();

    std::string generate(unsigned int seed);  // Returns starting location ID

    void movePlayer(Player& player, const std::string& direction);
    void describeCurrentTile(const Player& player) const;

    bool shouldTriggerCombat() const;
    Enemy getRandomEnemy() const;

    const std::unordered_map<std::string, Location>& getMap() const { return worldMap; }

private:
    int width, height;
    std::vector<std::vector<MapTile>> map;
    unsigned int worldSeed; 
    std::unordered_map<std::string, Location> worldMap;
};
