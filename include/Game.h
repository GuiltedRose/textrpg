#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <string>

class Game {
public:
    Game(); // Explicit constructor declaration
    void run();
    void showMenu();
    int getUserChoice();
    void showPlayerStats();
    void trainSkill();

private:
    Player player; // This must be initialized in Game's constructor
    void displayMenu();
    bool handleInput();
    void trainSkillMenu();
};

#endif // GAME_H
