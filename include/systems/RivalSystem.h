#ifndef RIVALSYSTEM_H
#define RIVALSYSTEM_H

#include <vector>
#include <memory>
#include "gameobjects/Enemy.h"

class RivalSystem {
public:
    RivalSystem(int notorietyThreshold = 10);

    void registerEnemy(std::shared_ptr<Enemy> enemy);
    void evaluateEnemies();
    const std::vector<std::shared_ptr<Enemy>>& getRivals() const;

private:
    int notorietyThreshold;
    std::vector<std::shared_ptr<Enemy>>& allEnemies;
    std::vector<std::shared_ptr<Enemy>>& rivals;
};

#endif