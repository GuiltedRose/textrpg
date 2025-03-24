#include "gameobjects/Enemy.h"
#include "systems/RivalSystem.h"

Enemy::Enemy(std::string name, std::string faction, int level)
    : name(std::move(name)), faction(std::move(faction)), level(level), notoriety(0), rivalStatus(false), rank(RivalRank::None) {}

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

EnemyType Enemy::getType() const {
    return type;
}

RivalRank Enemy::getRank() const {
    return rank;
}

void Enemy::increaseNotoriety(int amount) {
    notoriety += amount;
}

void Enemy::notorietyReset() {
    notoriety = 0;
}

int Enemy::getRivalLevel() const {
    return rivalLevel;
}

void Enemy::evaluateRivalLevel(int threshold) {
    while(notoriety >= threshold) {
        rivalLevel++;
        notoriety -= threshold;
        threshold *= 2;
    }
}

void Enemy::promoteRival(RivalRank newRank) {
    rivalStatus = true;
    rank = newRank;
    level += 2; // Example level boost for promotion
} 

void Enemy::setType(EnemyType enemyType) {
    type = enemyType;
} 

std::string Enemy::getRankString() const {
    return RivalSystem::rankToString(rank);
}