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

    void addItem(const Item& item);
    void showInventory() const;

    void displayStats() const;
    void trainSkill(const std::string& skill, int amount);

    static const std::set<std::string>& getValidSkills();
    const std::string& getName() const;
    std::map<std::string, int>& getSkills();
    std::map<std::string, int>& getSkillXP();

    // Add these
    int getLevel() const;
    int getXP() const;
    int getHealth() const;
    int getStamina() const;
    int getGold() const;

    void setLevel(int lvl);
    void setXP(int xp);
    void setHealth(int h);
    void setStamina(int s);
    void setGold(int g);
    void setName(const std::string& name);

    std::string getInventoryString() const;
    std::string getSkillsString() const;
    std::string getSkillXPString() const;

    void loadInventoryFromString(const std::string& inventory);
    void loadSkillsFromString(const std::string& skills);
    void loadSkillXPFromString(const std::string& skill_xp);

private:
    std::string name;
    int level;
    int xp;
    int gold;

    int health;
    int stamina;
    int mana;

    std::vector<Item> inventory;

    static const std::set<std::string> validSkills;
    std::map<std::string, int> skills;
    std::map<std::string, int> skillXP;

    const int xpThreshold = 100;
    void levelUpSkill(const std::string& skill);


};

#endif // PLAYER_H