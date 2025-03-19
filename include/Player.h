#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>
#include <set>

class Player {
public:
    explicit Player(std::string name); // Explicit to avoid implicit conversions

    void displayStats() const;
    void trainSkill(const std::string& skill, int amount);

private:
    std::string name;
    int health;
    int stamina;
    int mana;
    
    static const std::set<std::string> validSkills;
    std::map<std::string, int> skills;
};

#endif // PLAYER_H
