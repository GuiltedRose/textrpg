#ifndef GAME_H
#define GAME_H

#include "gameobjects/Player.h"
#include "systems/WorldGenerator.h"
#include "systems/SaveSystem.h"
#include "systems/CombatManager.h"
#include "game_state.h"
#include "GameWindow.h"
#include "World.h"
#include <string>

class Game {
public:
    Game(GameWindow* gameWindow); // Explicit constructor declaration
    void run();
    void update();
    bool isGameOver() const;

private:
    // Player stuffs
    Player player;
    World world;
    CombatManager combatManager;
    RivalSystem rivalSystem;

    GameWindow* window;

    // GameState displays
    void inventoryMenu();

    bool isRunning = true;
    bool inCombat = false;

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

    // Helper methods
    Player initializePlayer();
    void initializeGame();
    void setupNewGame();
    void addStartingItems();
    GameState updateState(GameState state);
    void handleInventoryAction(size_t index);
};

#endif // GAME_H