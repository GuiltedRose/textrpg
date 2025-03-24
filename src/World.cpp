#include "World.h"
#include <iostream>

World::World() {
    width = 10;
    height = 10;
    map.resize(height, std::vector<MapTile>(width, MapTile()));
}

void World::movePlayer(Player& player, const std::string& direction) {
    // Placeholder logic
    std::cout << "You move " << direction << ".\n";
    player.setPosition("UpdatedLocation"); // or update x/y if you track it
}

void World::describeCurrentTile(const Player& player) const {
    std::cout << "You are standing in an open field.\n"; // placeholder
}

bool World::shouldTriggerCombat() const {
    return rand() % 100 < 20; // 20% chance
}

Enemy World::getRandomEnemy() const {
    return Enemy("Goblin", "Monsters", 3);
}
