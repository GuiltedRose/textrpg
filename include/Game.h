#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "SaveGame.h"
#include <string>

class Game {
public:
    Game(); // Explicit constructor declaration
    void run();
    void displayMenu();
    bool handleInput();
    void trainSkillMenu();
    void saveGame();
    void loadGame();



private:
    Player player;


};

#endif // GAME_H
