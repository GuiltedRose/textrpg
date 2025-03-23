#include "gameobjects/Inventory.h"
#include "gameobjects/Player.h"
#include <iostream>
#include <sstream>

void Inventory::addItem(const Item& item) {
    items.push_back(item);
}

bool Inventory::removeItem(size_t index) {
    if (index >= items.size()) return false;

    std::cout << "You dropped: " << items[index].getName() << "\n";
    items.erase(items.begin() + index);
    return true;
}

const std::vector<Item>& Inventory::getItems() const {
    return items;
}

bool Inventory::useItem(size_t index, Player& player) {
    if (index >= items.size()) return false;

    const Item& item = items[index];
    if (item.getName() == "Health Potion") {
        player.setHealth(player.getHealth() + 20);  // heal 20
        std::cout << "You used a Health Potion! +20 HP.\n";
        removeItem(index);
        return true;
    }

    std::cout << "This item can't be used.\n";
    return false;
}

void Inventory::inspectItem(size_t index) const {
    if (index >= items.size()) {
        std::cout << "Invalid item selection.\n";
        return;
    }

    const Item& item = items[index];
    std::cout << "\nItem: " << item.getName() << "\n" << "Description: " << item.getDescription() << "\n";
}

std::string Inventory::serialize() const {
    std::string data;
    for(size_t i=0; i < items.size(); ++i) {
        data += items[i].getName() + "|" + items[i].getDescription();
        if(i < items.size() - 1) data += ",";
    }
    return data;
}

void Inventory::deserialize(const std::string& data) {
    items.clear();
    std::stringstream ss(data);
    std::string entry;
    while(std::getline(ss, entry, ',')) {
        auto sep = entry.find('|');
        if(sep != std::string::npos) {
            std::string name = entry.substr(0, sep);
            std::string desc = entry.substr(sep + 1);
            items.emplace_back(name, desc);
        }
    }
}

void Inventory::display() const {
    if(items.empty()) {
        std::cout << "Your inventory is empty...\n";
        return;
    }

    std::cout << "\n=== Inventory ===\n";
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << i + 1 << ". " << items[i].getName() << "\n";
    }
}