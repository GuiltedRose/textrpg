#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    Item(const std::string& name, const std::string& description);
    Item(const std::string& name); // Added this constructor

    std::string getName() const;

private:
    std::string name;
    std::string description;
};

#endif