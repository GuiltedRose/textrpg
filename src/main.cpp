#include "Game.h"
#include "tools/GameLogger.h"
#include "platforms/PlatformFactory.h"
#include "systems/SaveSystem.h"
#include <memory>
#include <iostream>

int main(int argc, char** argv) {
    // Create platform window (Vulkan-capable, from factory)
    std::unique_ptr<GameWindow> window = CreatePlatformWindow("Text RPG", 800, 600);

    // Set log overlay hook (optional)
    GameLogger::setOverlayCallback([](const std::string& msg) {
        // Placeholder: Vulkan overlay hook could go here
    });

    Game game;

    // === Initialization ===
    char choice;
    std::cout << "Load saved game? (y/n): ";
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 'y' || choice == 'Y') {
        std::string saveName;
        std::cout << "Enter save name (or press Enter for default): ";
        std::getline(std::cin, saveName);
        if (saveName.empty()) saveName = "save";

        PlayerData pdata;
        WorldData wdata;
        SaveManager::loadGame(pdata, wdata, saveName);

        if (pdata.name.empty()) {
            GameLogger::info("No valid save found. Starting new game...");
            game.initializeNewGame();
        } else {
            game.loadFromSave(pdata, wdata);
        }
    } else {
        game.initializeNewGame();
    }

    // === Main Game Loop (placeholder for now) ===
    while (true) {
        window->PollEvents();
        if (window->ShouldClose()) break;

        // Placeholder: future Vulkan frame logic
        window->clear();

        GameLogger::info("[Vulkan] Frame rendered here...");
        window->refresh();
    }

    // === Save on Exit ===
    char saveChoice;
    std::cout << "Save before quitting? (y/n): ";
    std::cin >> saveChoice;

    if (saveChoice == 'y' || saveChoice == 'Y') {
        std::string saveName;
        std::cout << "Enter save name (or press Enter for default): ";
        std::cin.ignore();
        std::getline(std::cin, saveName);
        if (saveName.empty()) saveName = "save";

        PlayerData pdata;
        pdata.name = game.player.getName();
        pdata.health = game.player.getHealth();
        pdata.position = game.player.getPosition();
        pdata.skills = game.player.getSkills();
        pdata.skillXP = game.player.getSkillXP();
        pdata.inventory = game.player.getInventoryString();

        WorldData wdata;
        wdata.location = game.player.getPosition();
        wdata.time = "day";
        wdata.seed = game.worldSeed;

        SaveManager::saveGame(pdata, wdata, saveName);
        GameLogger::info("Game saved as \"" + saveName + "\".");
    }

    return 0;
}
