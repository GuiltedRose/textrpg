#include "screens/TitleScreen.h"
#include "tools/GameLogger.h"
#include "systems/SaveSystem.h"

static const std::vector<std::string> menuOptions = {
    "New Game",
    "Load Game",
    "Exit"
};

namespace TitleScreen {

    GameState updateAndDraw(GameWindow& window, Game& game, VulkanRenderer& renderer) {
        static int selectedIndex = 0;

        // Draw the title ASCII
        int screenWidth = renderer.getFramebufferWidth();
        int screenHeight = renderer.getFramebufferHeight();
        int fontWidth = 8;
        int fontHeight = 8;

        int charsWide = screenWidth / fontWidth;
        int charsHigh = screenHeight / fontHeight;

        int maxTitleWidth = 0;
        for (const auto& line : asciiArt)
            maxTitleWidth = std::max(maxTitleWidth, (int)line.length());

        int xOffset = (charsWide - maxTitleWidth) / 2;
        int yOffset = 2;

        for (size_t i = 0; i < asciiArt.size(); ++i) {
            renderer.drawTextOverlayLine(asciiArt[i], xOffset, yOffset + static_cast<int>(i));
        }

        // Draw menu
        int menuY = yOffset + static_cast<int>(asciiArt.size()) + 2;
        for (size_t i = 0; i < menuOptions.size(); ++i) {
            std::string line = (selectedIndex == (int)i ? "> " : "  ") + menuOptions[i];
            renderer.drawTextOverlayLine(line, xOffset, menuY + static_cast<int>(i));
        }

        // Handle input (placeholder — replace with real key detection)
        if (window.isKeyPressed("up")) {
            selectedIndex = (selectedIndex - 1 + menuOptions.size()) % menuOptions.size();
        }
        if (window.isKeyPressed("down")) {
            selectedIndex = (selectedIndex + 1) % menuOptions.size();
        }
        if (window.isKeyPressed("enter")) {
            if (selectedIndex == 0) {
                game.initializeNewGame();
                return GameState::Exploring;
            } else if (selectedIndex == 1) {
                PlayerData pdata;
                WorldData wdata;
                SaveManager::loadGame(pdata, wdata, "save");
                if (pdata.name.empty()) {
                    GameLogger::info("No valid save found. Starting new game...");
                    game.initializeNewGame();
                } else {
                    game.loadFromSave(pdata, wdata);
                }
                return GameState::Exploring;
            } else {
                return GameState::Exit;
            }
        }

        return GameState::TitleScreen;
    }

}
