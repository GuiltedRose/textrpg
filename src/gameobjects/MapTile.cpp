#include "MapTile.h"

MapTile::MapTile(const std::string& desc, bool walkable)
    : description(desc), walkable(walkable) {}