#include "systems/RivalSystem.h"

RivalSystem::RivalSystem(int notorietyThreshold)
    : notorietyThreshold(notorietyThreshold) {}

void RivalSystem::registerEnemy(std::shared_ptr<Enemy> enemy) {
    allEnemies.push_back(enemy);
}

void RivalSystem::evaluateEnemies() {
    for (auto& enemy : allEnemies) {
        if (!enemy->isRival() && enemy->getNotoriety() >= notorietyThreshold) {
            enemy->promoteRival();
            rivals.push_back(enemy);
        }
    }
}

const std::vector<std::shared_ptr<Enemy>>& RivalSystem::getRivals() const {
    return rivals;
}
