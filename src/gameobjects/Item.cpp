#include "gameobjects/Item.h"

Item::Item(const std::string& name, const std::string& description, ItemType type)
    : name(name), description(description), type(type) {}

Item::Item(const std::string& name)
    : name(name), description("No description."), type(ItemType::Generic) {}

const std::string& Item::getName() const {
    return name;
}

const std::string& Item::getDescription() const {
    return description;
}

ItemType Item::getType() const {
    return type;
}
