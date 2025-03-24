#pragma once

#include "gameobjects/Player.h"
#include "gameobjects/Enemy.h"
#include "systems/RivalSystem.h"
#include <memory>

class CombatManager {
public:
    void startCombat(Player& player, std::shared_ptr<Enemy> enemy, RivalSystem& rivalSystem);
    void update(Player& player);

    bool isCombatActive() const;

private:
    std::shared_ptr<Enemy> currentEnemy;
    RivalSystem* rivalSystemRef = nullptr;
    bool playerTurn = true;
    bool activeCombat = false;

    void playerAttack(Player& player);
    void enemyAttack(Player& player);
    bool tryToFlee();
};
