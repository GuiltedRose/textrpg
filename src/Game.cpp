#include "Game.h"
#include "GameLogger.h"
#include "World.h"

Game::Game() : player("Default") {}

void Game::initializeNewGame(unsigned int seed) {
    if (seed == 0) {
        seed = static_cast<unsigned int>(std::time(nullptr));
    }

    worldSeed = seed;
    std::string startLoc = world.generate(seed);
    player.setPosition(startLoc);

    for (const auto& skill : player.getValidSkills()) {
        player.getSkills()[skill] = 0;
        player.getSkillXP()[skill] = 0;
    }

    addStartingItems();
}
void Game::loadFromSave(const PlayerData& pdata, const WorldData& wdata) {
    player.setName(pdata.name);
    player.setHealth(pdata.health);
    player.setPosition(pdata.position);
    player.loadInventoryFromString(pdata.inventory);
    player.getSkills() = pdata.skills;
    player.getSkillXP() = pdata.skillXP;

    worldSeed = wdata.seed;
    std::string ignoreStart = world.generate(worldSeed);
}

void Game::addStartingItems() {
    Item sword("Sword", "A sharp blade for combat", ItemType::Weapon);
    player.addItem(sword);
}
