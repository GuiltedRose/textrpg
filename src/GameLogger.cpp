#include "GameLogger.h"

GameWindow* GameLogger::window = nullptr;

void GameLogger::setWindow(GameWindow* gw) {
    window = gw;
}

void GameLogger::info(const std::string& message) {
    std::cout << message << std::endl;
    if (window) {
        window->drawText(message);
        window->refresh();
    }
}

void GameLogger::clear() {
    if (window) {
        window->clear();
    }
}