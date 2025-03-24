#include "PlatformFactory.h"
#include "Game.h"

int main(int argc, char* argv[]) {
    GameWindow* window = PlatformFactory::createGameWindow();
    window->createWindow();

    Game game(window);
    
    // Optional: Start window loop if needed (platform-specific)
    // window->run();  // Only do this if you want full event loop integration

    while (!game.isGameOver()) {
        game.update();
    }

    delete window;
    return 0;
}