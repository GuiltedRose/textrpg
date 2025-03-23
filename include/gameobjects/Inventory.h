#pragma once

#include "gameobjects/Item.h"
#include <vector>
#include <string>
class Player;
class Inventory {
public:
    void addItem(const Item& item);
    bool useItem(size_t index, Player& player);
    bool removeItem(size_t index);
    void inspectItem(size_t index) const;

    const std::vector<Item>& getItems() const;

    std::string serialize() const;
    void deserialize(const std::string& data);

    void display() const;
private:
    std::vector<Item> items;
};