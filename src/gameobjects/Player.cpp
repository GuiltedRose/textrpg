#include "gameobjects/Player.h"
#include <iostream>
#include <sstream>

// Define valid skills
const std::set<std::string> Player::validSkills = {
    "Swordsmanship", "Archery", "Unarmed Combat",
    "Fire Magic", "Water Magic", "Healing Magic",
    "Stealth", "Foraging", "Crafting",
    "Persuasion", "Bartering", "Intimidation"
};

Player::Player(std::string name) : name(std::move(name)), level(1), xp(0), gold(0), health(100), stamina(100), mana(50) {}


void Player::displayStats() const {
    std::cout << "\n=== " << name << "'s Stats ===\n";
    std::cout << "Health: " << health << "\n";
    std::cout << "Stamina: " << stamina << "\n";
    std::cout << "Mana: " << mana << "\n";
    std::cout << "Skills:\n";
    for (const auto& [skill, level] : skills) {
        // Display both level and XP
        std::cout << " - " << skill << ": Level " << level << " | XP: " << skillXP.at(skill) << "\n";
    }
}

void Player::trainSkill(const std::string& skill, int amount) {
    if (validSkills.find(skill) == validSkills.end()) {
        std::cout << "Error: " << skill << " is not a recognized skill.\n";
        return;
    }

    // Add XP to the skill
    skillXP[skill] += amount;
    std::cout << "You gained " << amount << " XP in " << skill << "!\n";

    // Level up if XP threshold is reached
    if (skillXP[skill] >= xpThreshold) {
        levelUpSkill(skill);
    }
}

void Player::levelUpSkill(const std::string& skill) {
    // Increase skill level
    skills[skill] += 1;
    skillXP[skill] = 0;  // Reset XP after leveling up
    std::cout << skill << " has leveled up! It is now level " << skills[skill] << ".\n";
}

void Player::loadInventoryFromString(const std::string& data) {
    inventory.deserialize(data);
}

void Player::loadSkillsFromString(const std::string& skillsStr) {
    skills.clear();
    std::stringstream ss(skillsStr);
    std::string skill;
    while (std::getline(ss, skill, ',')) {
        skills[skill] = 0; // Default to level 0 if not specified
    }
}

void Player::loadSkillXPFromString(const std::string& skillXPStr) {
    skillXP.clear();
    std::stringstream ss(skillXPStr);
    std::string pair;
    while (std::getline(ss, pair, ',')) {
        size_t pos = pair.find(':');
        if (pos != std::string::npos) {
            std::string skill = pair.substr(0, pos);
            int xp = std::stoi(pair.substr(pos + 1));
            skillXP[skill] = xp;
        }
    }
}

void Player::addItem(const Item& item) {
    inventory.addItem(item);
}

void Player::showInventory() const {
    inventory.display();
}

void Player::equipWeapon(const Item& item) {
    equippedWeapon = item;
    std::cout << "You Equipped " << item.getName() << std::endl;
}

// Getters

std::string Player::getInventoryString() const {
   return inventory.serialize();
}

Inventory& Player::getInventory() {
    return inventory;
}

const Inventory& Player::getInventory() const {
    return inventory;
}

const Item& Player::getEquippedWeapon() const {
    return equippedWeapon;
}

const std::string& Player::getName() const {
    return name;
}


std::string Player::getSkillsString() const {
    std::string result;
    for (const auto& skill : skills) {
        if (!result.empty()) result += ",";
        result += skill.first;
    }
    return result;
}

std::string Player::getSkillXPString() const {
    std::string result;
    for (const auto& xp : skillXP) {
        if (!result.empty()) result += ",";
        result += xp.first + ":" + std::to_string(xp.second);
    }
    return result;
}

const std::set<std::string>& Player::getValidSkills() {
    return validSkills;
}

std::map<std::string, int>& Player::getSkills() {
    return skills;
}

std::map<std::string, int>& Player::getSkillXP() {
    return skillXP;
}

int Player::getLevel() const {
    return level;
}

int Player::getXP() const {
    return xp;
}

int Player::getHealth() const {
    return health;
}

int Player::getStamina() const {
    return stamina;
}

int Player::getGold() const {
    return gold;
}

std::string Player::getPosition() const {
    return position;
}

// Setters

void Player::setLevel(int lvl) {
    level = lvl;
}

void Player::setXP(int x) {
    xp = x;
}

void Player::setHealth(int h) {
    health = h;
}

void Player::setStamina(int s) {
    stamina = s;
}

void Player::setGold(int g) {
    gold = g;
}

void Player::setName(const std::string& newName) {
    name = newName;
}

void Player::setPosition(const std::string& newPos) {
    position = newPos;
}
