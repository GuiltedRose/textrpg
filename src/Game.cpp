#include "Game.h"
#include <iostream>

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
    bool isRunning = true;
    while (isRunning) {
        displayMenu();
        isRunning = handleInput();
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

bool Game::handleInput() {
    int choice;
    std::cin >> choice;
    std::cin.ignore();

    switch (choice) {
        case 1:
            trainSkillMenu();
            break;
        case 2:
            player.displayStats();
            break;
        case 3:
            saveGame();
            break;
        case 4:
            std::cout << "Exiting game...\n";
            return false;
        default:
            std::cout << "Invalid choice, try again.\n";
            break;
    }
    return true;
}

void Game::trainSkillMenu() {
    std::string skill;
    std::cout << "Enter the skill you want to train: ";
    std::getline(std::cin, skill);

    player.trainSkill(skill, 10);  // Give 10 XP for training a skill
}

// Convert Player Data to a Map and Save It
void Game::saveGame() {
    std::unordered_map<std::string, std::string> playerData;
    
    playerData["name"] = player.getName();
    playerData["level"] = std::to_string(player.getLevel());
    playerData["xp"] = std::to_string(player.getXP());
    playerData["health"] = std::to_string(player.getHealth());
    playerData["stamina"] = std::to_string(player.getStamina());
    playerData["gold"] = std::to_string(player.getGold());

    // Convert inventory to a comma-separated string
    playerData["inventory"] = player.getInventoryString();
    
    // Convert skills and XP to comma-separated values
    playerData["skills"] = player.getSkillsString();
    playerData["skill_xp"] = player.getSkillXPString();

    std::string filename;
    std::cout << "Enter save file name (or press Enter for default): ";
    std::getline(std::cin, filename);
    if (filename.empty()) filename = "save.txt";

    SaveSystem::saveGame(playerData, filename);
}

// Load Player Data from a Map
void Game::loadGame() {
    std::string filename;
    std::cout << "Enter save file name (or press Enter for default): ";
    std::getline(std::cin, filename);
    if (filename.empty()) filename = "save.txt";

    std::unordered_map<std::string, std::string> playerData;
    SaveSystem::loadGame(playerData, filename);

    if (playerData.empty()) {
        std::cout << "No valid save data found.\n";
        return;
    }

    // Assign loaded values to player
    player.setName(playerData["name"]);
    player.setLevel(std::stoi(playerData["level"]));
    player.setXP(std::stoi(playerData["xp"]));
    player.setHealth(std::stoi(playerData["health"]));
    player.setStamina(std::stoi(playerData["stamina"]));
    player.setGold(std::stoi(playerData["gold"]));

    // Load inventory, skills, and skill XP
    player.loadInventoryFromString(playerData["inventory"]);
    player.loadSkillsFromString(playerData["skills"]);
    player.loadSkillXPFromString(playerData["skill_xp"]);
}
