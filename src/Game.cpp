#include "Game.h"
#include <iostream>

// Explicit constructor that properly initializes the Player instance
Game::Game() : player("Hero") {} // Ensures Player gets a name

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

    player.trainSkill(skill, 1);
}
