#include "Game.h"
#include <iostream>
#include <ctime>

Game::Game() : player([] {
        std::string name;
        std::cout << "Enter your character's name (or press Enter for 'Hero'): ";
        std::getline(std::cin, name);
        if (name.empty()) name = "Hero";
        return Player(name);
    }()) {

    // Ask if the player wants to load a saved game
    std::cout << "Load saved game? (y/n): ";
    char choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 'y' || choice == 'Y') {
        loadGame();
    } else {
        // Step 1: Add our Seed
        unsigned int seed;
        std::cout << "Enter a world seed? (0 for random): ";
        std::cin >> seed;
        std::cin.ignore();

        if(seed == 0) seed = static_cast<unsigned int>(std::time(nullptr));
        worldSeed = seed;

        // Step 2: Generate World
        std::string startLoc;
        worldMap = WorldGenerator::generateMap(10, startLoc, seed);

        // Step 3: Placing player
        player.setPosition(startLoc);

        // Initialize skills to level 0 and XP 0 for all valid skills
        for (const auto& skill : player.getValidSkills()) {
            player.getSkills()[skill] = 0;    // Initial level of the skill is 0
            player.getSkillXP()[skill] = 0;   // Initial XP of the skill is 0
        }
    }

    // Example of creating an item and adding it to the player's inventory
    Item sword("Sword", "A sharp blade for combat");
    player.addItem(sword);  // Assuming you've created a method to add items

}

void Game::run() {
    
    GameState state = GameState::MainMenu;

    while(state != GameState::Exit) {
        switch(state) {
            case GameState::MainMenu: 
                displayMenu();
                state = handleInput();
                break;
            case GameState::GameOver: 
                std::cout << "Game Over! Returning to Menu...\n";
                state = GameState::MainMenu;
                break;
            case GameState::Exit: 
                break;
            default: std::cout << "Unhandled Game State...\n";
                state = GameState::Exit;
                break;
        }
    }

    // Prompt to save before exiting
    std::cout << "Save game before exiting? (y/n): ";
    char choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 'y' || choice == 'Y') {
        saveGame();
    }
}

void Game::displayMenu() {
    std::cout << "\n=== Text RPG ===\n";
    std::cout << "1. Train a skill\n";
    std::cout << "2. View Stats\n";
    std::cout << "3. Save Game\n";
    std::cout << "4. Exit\n";
    std::cout << "Choose an action: ";
}

GameState Game::handleInput() {
    int choice;
    std::cin >> choice;
    std::cin.ignore();

    switch (choice) {
        case 1:
            trainSkillMenu();
            return GameState::MainMenu;
            break;
        case 2:
            player.displayStats();
            return GameState::MainMenu;
            break;
        case 3:
            saveGame();
            return GameState::MainMenu;
            break;
        case 4:
            std::cout << "Exiting game...\n";
            return GameState::Exit;
        default:
            std::cout << "Invalid choice, try again.\n";
            return GameState::MainMenu;
            break;
    }
    return GameState::MainMenu;
}

void Game::trainSkillMenu() {
    std::string skill;
    std::cout << "Enter the skill you want to train: ";
    std::getline(std::cin, skill);

    player.trainSkill(skill, 10);  // Give 10 XP for training a skill
}

// Convert Player Data to a Map and Save It
void Game::saveGame() {
    std::string saveName;
    std::cout << "Enter save name (or press Enter for default): ";
    std::getline(std::cin, saveName);
    if (saveName.empty()) saveName = "save";

    PlayerData pdata;
    pdata.name = player.getName();
    pdata.health = player.getHealth();
    pdata.position = player.getPosition();
    pdata.skills = player.getSkills();
    pdata.skillXP = player.getSkillXP();

    WorldData wdata;
    wdata.location = player.getPosition();
    wdata.time = "day";
    wdata.seed = worldSeed;

    SaveManager::saveGame(pdata, wdata, saveName);
    std::cout << "Game saved as \"" << saveName << "\".\n";
}


// Load Player Data from a Map
void Game::loadGame() {
    std::string saveName;
    std::cout << "Enter save name (or press Enter for default): ";
    std::getline(std::cin, saveName);
    if (saveName.empty()) saveName = "save";

    PlayerData pdata;
    WorldData wdata;

    SaveManager::loadGame(pdata, wdata, saveName);

    if (pdata.name.empty()) {
        std::cout << "No valid save data found.\n";
        return;
    }

    player.setName(pdata.name);
    player.setHealth(pdata.health);
    player.setPosition(pdata.position);
    player.getSkills() = pdata.skills;
    player.getSkillXP() = pdata.skillXP;

    worldSeed = wdata.seed;
    std::string ignoreStart;
    worldMap = WorldGenerator::generateMap(10, ignoreStart, worldSeed);
}
