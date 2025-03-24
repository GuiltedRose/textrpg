#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include "RivalRank.h"  // Only need the enum, not the full RivalSystem

enum class EnemyType {
    Humanoid,
    Monster,
    BountyHunter
};

class Enemy {
public:
    Enemy(std::string name, std::string faction, int level);

    const std::string& getName() const;
    const std::string& getFaction() const;

    EnemyType getType() const;
    RivalRank getRank() const;

    int getHealth() const;

    int getRivalLevel() const;

    int getLevel() const;
    int getNotoriety() const;
    std::string getRankString() const;

    void setType(EnemyType enemyType);
    void setHealth(int newHP);

    bool isRival() const;

    void increaseNotoriety(int amount);
    void notorietyReset();
    void promoteRival(RivalRank rank);

private:
    std::string name;
    std::string faction;
    void evaluateRivalLevel(int threshold);
    int level = 1;
    int rivalLevel = 0;
    int threshold = 10;
    int notoriety;
    bool rivalStatus;
    int health;
    int newHP;

    EnemyType type;
    RivalRank rank = RivalRank::Unranked;
};

#endif