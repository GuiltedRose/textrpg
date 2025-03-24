#pragma once

#include "gameobjects/Player.h"
#include "gameobjects/Enemy.h"
#include "systems/RivalSystem.h"
#include <iostream>
#include <random>

class CombatManager {
public:
    static void startCombat(Player& player, Enemy& enemy, RivalSystem& rivalSystem) {
        std::cout << "\nCombat begins between " << player.getName() << " and " << enemy.getName() << std::endl;

        while(player.getHealth() > 0 && enemy.getHealth() > 0) {
            std::cout << "\n === Your Turn ===\n";
            std::cout << "1. Attack\n";
            std::cout << "2. Flee\n";
            std::cout << "Choose an action: ";

            int choice;
            std::cin >> choice;
            std::cin.ignore();

            switch(choice) {
                case 1:
                    playerAttack(player, enemy);
                    break;
                case 2:
                    if(tryToFlee()) {
                        std::cout << "You fled successfully!\n";
                        return;
                    } else {
                        std::cout << "You failed to flee...\n";
                    }
                    break;
                default:
                    std::cout << "Invalid action, try again... ";
                    break;
            }

            if(enemy.getHealth() > 0) {
                enemyAttack(enemy, player);
            }
        }

        if(player.getHealth() <= 0) {
            std::cout << "You have been defeated by " << enemy.getName() << "...\n";
            enemy.notorietyReset();
        } else if(enemy.getHealth <= 0) {
            std::cout << "You have defeated " << enemy.getName() << "!\n";
            enemy.increaseNotoriety(2);
            rivalSystem.registerEnemy(std::make_shared<Enemy>(enemy));
            rivalSystem.evaluateEnemies();
        }
    }
private:
    static void playerAttack(Player& player, Enemy& enemy) {
        int damage = 10;
        std::cout << "You attack with " << player.equippedWeapon().getName() << " for " damage " damage!\n";
        enemy.setHealth(enemy.getHealth() - damage);
    }

    static void enemyAttack(Enemy& enemy, Player& player) {
        int damage = 5;
        std::cout << enemy.getName() " attacks you for " << damage << "!\n";
        player.setHealth(player.getHealth() - damage);
    }

    static bool tryToFlee() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 100);
        return dist(gen) <= 50;
    }
};