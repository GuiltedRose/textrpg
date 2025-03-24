// MapTile.h
#pragma once
#include <string>

class MapTile {
public:
    MapTile(const std::string& desc = "An empty field", bool walkable = true);

    std::string getDescription() const;
    bool isWalkable() const;

private:
    std::string description;
    bool walkable;
};