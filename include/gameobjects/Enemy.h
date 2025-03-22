#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
public:
    Enemy(std::string name, std::string faction, int level);

    const std::string& getName() const;
    const std::string& getFaction() const;
    int getLevel() const;
    int getNotoriety() const;
    bool isRival() const;

    void increaseNotoriety(int amount);
    void promoteRival();

private:
    std::string name;
    std::string faction;
    int level = 1;
    int notoriety;
    bool rivalStatus;
};

#endif