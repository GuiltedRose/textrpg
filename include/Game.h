#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <string>

class Game {
public:
    Game(); // Explicit constructor declaration
    void run();

private:
    Player player; // This must be initialized in Game's constructor
    void displayMenu();
    bool handleInput();
    void trainSkillMenu();
};

#endif // GAME_H
