#include "Player.h"
#include <iostream>

const std::set<std::string> Player::validSkills = {
    "Swordsmanship", "Archery", "Unarmed Combat",
    "Fire Magic", "Water Magic", "Healing Magic",
    "Stealth", "Foraging", "Crafting",
    "Persuasion", "Bartering", "Intimidation"
};

// Properly initialize Player
Player::Player(std::string name) : name(std::move(name)), health(100), stamina(100), mana(50) {}

void Player::displayStats() const {
    std::cout << "\n=== " << name << "'s Stats ===\n";
    std::cout << "Health: " << health << "\n";
    std::cout << "Stamina: " << stamina << "\n";
    std::cout << "Mana: " << mana << "\n";
    std::cout << "Skills:\n";
    for (const auto& [skill, level] : skills) {
        std::cout << " - " << skill << ": Level " << level << "\n";
    }
}

void Player::trainSkill(const std::string& skill, int amount) {
    if (validSkills.find(skill) == validSkills.end()) {
        std::cout << "Error: " << skill << " is not a recognized skill.\n";
        return;
    }

    skills[skill] += amount;
    std::cout << "You trained " << skill << "! It is now level " << skills[skill] << ".\n";
}
