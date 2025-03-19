#include <iostream>
#include "Game.h"

int main(int argc, char* argv[]) {
    std::cout << "Welcome to the game!" << std::endl;

    Game game;
    game.run();

    return 0;
}