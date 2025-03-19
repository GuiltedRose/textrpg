#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    Item(const std::string& name, const std::string& description);
    const std::string& getName() const;
    const std::string& getDescription() const;

private:
    std::string name;
    std::string description;
};

#endif // ITEM_H
