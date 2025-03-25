#pragma once

#include "Player.h"
#include "World.h"
#include "systems/CombatManager.h"
#include "systems/RivalSystem.h"
#include "systems/SaveSystem.h"
#include "game_state.h"

class Game {
public:
    Game();

    void initializeNewGame(unsigned int seed = 0);        // New game setup
    void loadFromSave(const PlayerData& pdata, const WorldData& wdata); // Load path
    void addStartingItems();

    // Systems and player state available to use from elsewhere
    Player player;
    World world;

    unsigned int worldSeed = 0;

private:
    CombatManager combatManager;
    RivalSystem rivalSystem;
};
