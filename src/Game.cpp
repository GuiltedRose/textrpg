#include "Game.h"
#include <iostream>

Game::Game() : player("Hero") {
    // Initialize skills to level 0 and XP 0 for all valid skills
    for (const auto& skill : player.getValidSkills()) {
        // Initialize each skill with level 0 and XP 0
        player.getSkills()[skill] = 0;    // Initial level of the skill is 0
        player.getSkillXP()[skill] = 0;   // Initial XP of the skill is 0
    }
}

void Game::run() {
    bool isRunning = true;
    while (isRunning) {
        displayMenu();
        isRunning = handleInput();
    }
}

void Game::displayMenu() {
    std::cout << "\n=== Text RPG ===\n";
    std::cout << "1. Train a skill\n";
    std::cout << "2. View Stats\n";
    std::cout << "3. Exit\n";
    std::cout << "Choose an action: ";
}

bool Game::handleInput() {
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            trainSkillMenu();
            break;
        case 2:
            player.displayStats();
            break;
        case 3:
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
    std::cin.ignore();
    std::getline(std::cin, skill);

    player.trainSkill(skill, 10);  // Give 10 XP for training a skill
}
