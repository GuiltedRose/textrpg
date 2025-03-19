#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>
#include <set>
#include <vector>
#include "gameobjects/Item.h"

class Player {
public:
    explicit Player(std::string name);

    // void addItem(const Item& item);
    // void showInventory() const;

    void displayStats() const;
    void trainSkill(const std::string& skill, int amount);
    
    // Change to return non-const references
    static const std::set<std::string>& getValidSkills() { return validSkills; }
    const std::string& getName() const;
    std::map<std::string, int>& getSkills() { return skills; }
    std::map<std::string, int>& getSkillXP() { return skillXP; }

private:
    std::string name;
    int health;
    int stamina;
    int mana;
    
    std::vector<Item> inventory;

    static const std::set<std::string> validSkills;
    std::map<std::string, int> skills;  // Skill level
    std::map<std::string, int> skillXP; // Skill XP
    const int xpThreshold = 100;        // XP required to level up
    void levelUpSkill(const std::string& skill);
};

#endif // PLAYER_H
