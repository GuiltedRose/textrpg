#include "gameobjects/Enemy.h"

Enemy::Enemy(std::string name, std::string faction, int level): name(name), faction(faction), notoriety(0), rivalStatus(false) {}

const std::string& Enemy::getName() const {
    return name;
}

const std::string& Enemy::getFaction() const {
    return faction;
}

int Enemy::getLevel() const {
    return level;
}

int Enemy::getNotoriety() const {
    return notoriety;
}

bool Enemy::isRival() const {
    return rivalStatus;
}

void Enemy::increaseNotoriety(int amount) {
    notoriety += amount;
}

void Enemy::promoteRival() {
    rivalStatus = true;
    level += 2;
}