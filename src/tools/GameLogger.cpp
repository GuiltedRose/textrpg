#include "GameLogger.h"

void (*GameLogger::overlayCallback)(const std::string&) = nullptr;

void GameLogger::info(const std::string& message) {
    std::cout << message << std::endl;

    if (overlayCallback) {
        overlayCallback(message); // Vulkan or other future handler
    }
}

void GameLogger::clear() {
    // Terminal clear fallback
    std::cout << "\033[2J\033[H"; // ANSI: clear screen + move cursor to top
}

void GameLogger::setOverlayCallback(void (*func)(const std::string&)) {
    overlayCallback = func;
}
