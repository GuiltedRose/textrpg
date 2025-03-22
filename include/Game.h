#ifndef GAME_H
#define GAME_H

#include "gameobjects/Player.h"
#include "systems/WorldGenerator.h"
#include "SaveGame.h"
#include "game_state.h"
#include <string>

class Game {
public:
    Game(); // Explicit constructor declaration
    void run();

private:
    // Player stuffs
    Player player;

    // Game Loop
    void displayMenu();
    GameState handleInput();
    void trainSkillMenu();

    // World Generation
    std::unordered_map<std::string, Location> worldMap;
    unsigned int worldSeed = 0;

    // Saving / Loading
    void saveGame();
    void loadGame();
};

#endif // GAME_H