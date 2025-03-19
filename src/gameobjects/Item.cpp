#include "Item.h"

Item::Item(const std::string& name, const std::string& description)
    : name(name), description(description) {}

const std::string& Item::getName() const {
    return name;
}

const std::string& Item::getDescription() const {
    return description;
}
