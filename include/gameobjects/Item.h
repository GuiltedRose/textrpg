#pragma once
#include <string>

enum class ItemType {
    Generic,
    Weapon,
    Armor,
    Consumable
};

class Item {
public:
    Item(const std::string& name, const std::string& description, ItemType type = ItemType::Generic);
    Item(const std::string& name);
    const std::string& getName() const;
    const std::string& getDescription() const;
    ItemType getType() const;

private:
    std::string name;
    std::string description;
    ItemType type;
};