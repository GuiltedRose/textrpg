#include "Player.h"
#include <iostream>

// Define valid skills
const std::set<std::string> Player::validSkills = {
    "Swordsmanship", "Archery", "Unarmed Combat",
    "Fire Magic", "Water Magic", "Healing Magic",
    "Stealth", "Foraging", "Crafting",
    "Persuasion", "Bartering", "Intimidation"
};

Player::Player(std::string name) : name(std::move(name)), health(100), stamina(100), mana(50) {}

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
