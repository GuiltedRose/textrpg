#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>
#include <set>
#include <vector>
#include "gameobjects/Item.h"
#include "gameobjects/Inventory.h"

class Player {
public:
    Player() : Player("Default") {}
    explicit Player(std::string name);
    bool isDead() const;

    // Calls to Inventory:
    void addItem(const Item& item);
    void showInventory() const;

    // Calls to Skills:
    void displayStats() const;
    void trainSkill(const std::string& skill, int amount);

    // Equipping Items from Inventory:
    void equipWeapon(const Item& item);

    // Getters
    Inventory& getInventory();
    const Inventory& getInventory() const;

    Item getEquippedWeapon() const;
    
    static const std::set<std::string>& getValidSkills();
    const std::string& getName() const;
    std::map<std::string, int>& getSkills();
    std::map<std::string, int>& getSkillXP();

    int getLevel() const;
    int getXP() const;

    int getHealth() const;
    int getCurrentHP() const;

    int getStamina() const;
    int getGold() const;   
    std::string getPosition() const; 

    // Setters
    void setLevel(int lvl);
    void setXP(int xp);
    void setHealth(int h);
    void setStamina(int s);
    void setGold(int g);
    void setName(const std::string& name);
    void setPosition(const std::string& newPos);

    // For Saving Data:

    std::string getInventoryString() const;
    std::string getSkillsString() const;
    std::string getSkillXPString() const;
    
    void loadInventoryFromString(const std::string& data);
    void loadSkillsFromString(const std::string& skills);
    void loadSkillXPFromString(const std::string& skill_xp);

private:
    
    std::string name;
    
    Inventory inventory;

    // Equipping Items from Inventory:
    Item equippedWeapon = Item("None", "No Weapon Equipped");

    int level;
    int xp;
    int gold;

    int health;
    int currentHP;

    int stamina;
    int mana;

    static const std::set<std::string> validSkills;
    std::map<std::string, int> skills;
    std::map<std::string, int> skillXP;

    const int xpThreshold = 100;
    void levelUpSkill(const std::string& skill);

    std::string position = "unknown";
};

#endif // PLAYER_H