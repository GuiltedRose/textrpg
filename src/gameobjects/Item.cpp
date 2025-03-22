#include <string>
#include "gameobjects/Item.h"

Item::Item(const std::string& name, const std::string& description)
    : name(name), description(description) {}

Item::Item(const std::string& name)
    : name(name), description("An unknown item.") {}

std::string Item::getName() const {
    return name;
}