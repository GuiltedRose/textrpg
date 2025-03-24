#include "systems/RivalSystem.h"

RivalSystem::RivalSystem(int notorietyThreshold)
    : notorietyThreshold(notorietyThreshold) {}

void RivalSystem::registerEnemy(std::shared_ptr<Enemy> enemy) {
    allEnemies.push_back(enemy);
}

void RivalSystem::evaluateEnemies() {
    for (auto& enemy : allEnemies) {
        if (!enemy->isRival() && enemy->getNotoriety() >= notorietyThreshold) {
            RivalRank rank = determineRank(enemy->getRivalLevel(), enemy->getType());
            enemy->promoteRival(rank);
            rivals.push_back(enemy);
        }
    }
}

const std::vector<std::shared_ptr<Enemy>>& RivalSystem::getRivals() const {
    return rivals;
}

RivalRank RivalSystem::determineRank(int rivalLevel, EnemyType type) {
    switch (type) {
        case EnemyType::Monster:
            if (rivalLevel >= 40) return RivalRank::Alpha;
            if (rivalLevel >= 25) return RivalRank::Beast;
            if (rivalLevel >= 15) return RivalRank::Menace;
            return RivalRank::Unranked;

        case EnemyType::BountyHunter:
            if (rivalLevel >= 50) return RivalRank::EliteHunter;
            if (rivalLevel >= 30) return RivalRank::Tracker;
            if (rivalLevel >= 15) return RivalRank::Scout;
            return RivalRank::Unranked;

        case EnemyType::Humanoid:
        default:
            if (rivalLevel >= 45) return RivalRank::Boss;
            if (rivalLevel >= 30) return RivalRank::Scientist;
            if (rivalLevel >= 20) return RivalRank::Manager;
            if (rivalLevel >= 10) return RivalRank::Underling;
            return RivalRank::Unranked;
    }
}

std::string RivalSystem::rankToString(RivalRank rank) {
    switch (rank) {
        case RivalRank::Underling: return "Underling";
        case RivalRank::Manager: return "Manager";
        case RivalRank::Scientist: return "Scientist";
        case RivalRank::Boss: return "Boss";
        case RivalRank::Scout: return "Scout";
        case RivalRank::Tracker: return "Tracker";
        case RivalRank::EliteHunter: return "Elite Hunter";
        case RivalRank::Menace: return "Menace";
        case RivalRank::Beast: return "Beast";
        case RivalRank::Alpha: return "Alpha";
        default: return "Unranked";
    }
}
