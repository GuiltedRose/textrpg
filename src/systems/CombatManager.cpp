#include "systems/CombatManager.h"
#include <iostream>
#include <random>

void CombatManager::startCombat(Player& player, std::shared_ptr<Enemy> enemy, RivalSystem& rivalSystem) {
    currentEnemy = enemy;
    rivalSystemRef = &rivalSystem;
    activeCombat = true;
    playerTurn = true;

    std::cout << "\nCombat begins between " << player.getName() << " and " << enemy->getName() << "\n";
}

void CombatManager::update(Player& player) {
    if (!activeCombat || !currentEnemy) return;

    if (playerTurn) {
        std::cout << "\n=== Your Turn ===\n";
        std::cout << "1. Attack\n2. Flee\nChoose an action: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            choice = 1;
        }

        std::cin.ignore(); // clear newline

        switch (choice) {
            case 1:
                playerAttack(player);
                break;
            case 2:
                if (tryToFlee()) {
                    std::cout << "You fled successfully!\n";
                    activeCombat = false;
                    return;
                } else {
                    std::cout << "You failed to flee...\n";
                }
                break;
            default:
                std::cout << "Invalid action. Skipping turn.\n";
                break;
        }

        if (currentEnemy->getHealth() <= 0) {
            std::cout << "You defeated " << currentEnemy->getName() << "!\n";
            currentEnemy->increaseNotoriety(2);
            if (rivalSystemRef)
                rivalSystemRef->registerEnemy(currentEnemy);
            rivalSystemRef->evaluateEnemies();
            activeCombat = false;
            return;
        }

        playerTurn = false;
    } else {
        enemyAttack(player);

        if (player.getCurrentHP() <= 0) {
            std::cout << "You were defeated by " << currentEnemy->getName() << "...\n";
            currentEnemy->notorietyReset();
            activeCombat = false;
            return;
        }

        playerTurn = true;
    }
}

void CombatManager::playerAttack(Player& player) {
    int damage = 10;
    std::cout << "You attack with " << player.getEquippedWeapon().getName()
              << " for " << damage << " damage!\n";
    currentEnemy->setHealth(currentEnemy->getHealth() - damage);
}

void CombatManager::enemyAttack(Player& player) {
    int damage = 5;
    std::cout << currentEnemy->getName() << " attacks you for " << damage << "!\n";
    player.setHealth(player.getCurrentHP() - damage);
}

bool CombatManager::tryToFlee() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);
    return dist(gen) <= 50;
}

bool CombatManager::isCombatActive() const {
    return activeCombat;
}
