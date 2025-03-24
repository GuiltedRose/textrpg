#pragma once
#include "MapTile.h"
#include "Player.h"
#include "systems/CombatManager.h"
#include "gameobjects/Enemy.h"
#include <vector>

class World {
public:
    World();

    void movePlayer(Player& player, const std::string& direction);
    void describeCurrentTile(const Player& player) const;

    bool shouldTriggerCombat() const;
    Enemy getRandomEnemy() const;

private:
    std::vector<std::vector<MapTile>> map;
    int width, height;

    World(const World&) = delete;
    World& operator=(const World&) = delete;
};