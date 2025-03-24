#pragma once

#include "RivalRank.h"
#include "gameobjects/Enemy.h"
#include <vector>
#include <memory>

class RivalSystem {
public:
    RivalSystem(int notorietyThreshold = 10);

    void registerEnemy(std::shared_ptr<Enemy> enemy);
    void evaluateEnemies(); // Check and promote if needed
    const std::vector<std::shared_ptr<Enemy>>& getRivals() const;

    static RivalRank determineRank(int notoriety, EnemyType type);
    static std::string rankToString(RivalRank rank);

private:
    int notorietyThreshold;
    std::vector<std::shared_ptr<Enemy>> allEnemies;
    std::vector<std::shared_ptr<Enemy>> rivals;
};