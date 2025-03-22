#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <random>
#include <algorithm>

struct Location {
    std::string id;
    std::string name;
    std::string description;
    std::vector<std::string> connections;
};

class WorldGenerator {
public:
    static std::unordered_map<std::string, Location> generateMap(int numLocations, std::string& startLocationId, unsigned int seed) {
        std::unordered_map<std::string, Location> map;
        std::vector<std::string> names = {
            "Forest", "Cave", "Village", "Ruins", "Lake",
            "Mountain Pass", "Ancient Tree", "Campfire Site", "Abandoned Cabin", "Hidden Shrine"
        };

        std::vector<std::string> descriptions = {
            "A mysterious place shrouded in fog.",
            "You hear distant whispers in the wind.",
            "It feels oddly peaceful here.",
            "Something ancient was built here long ago.",
            "The air is heavy with magic."
        };

        std::mt19937 rng(seed);
        std::uniform_int_distribution<int> nameDist(0, names.size() -1);
        std::uniform_int_distribution<int> descDist(0, descriptions.size() -1);

        // Step 1: Generating Locations
        for(int i = 0; i < numLocations; ++i) {
            std::string id = "loc" + std::to_string(i);
            std::string name = names[nameDist(rng)];
            std::string description = descriptions[descDist(rng)];

            map[id] = Location{id, name, description, {}};
        }

        // Step 2: Collect nodes to graph
        for(int i = 1; i < numLocations; ++i) {
            std::string from = "loc" + std::to_string(i - 1);
            std::string to = "loc" + std::to_string(i);
            map[from].connections.push_back(to);
            map[to].connections.push_back(from);
        }

        // Step 3: Add random extra connections
        std::uniform_int_distribution<int>connectionDist(0, numLocations - 1);
        
        for(int i = 0; i < numLocations / 2; ++i) {
            std::string a = "loc" + std::to_string(connectionDist(rng));
            std::string b = "loc" + std::to_string(connectionDist(rng));

            if(a != b && std::find(map[a].connections.begin(), map[a].connections.end(), b) == map[a].connections.end()) {
                map[a].connections.push_back(b);
                map[b].connections.push_back(a);
            }
        }

        std::uniform_int_distribution<int> startDist(0, numLocations - 1);
        startLocationId = "loc" + std::to_string(startDist(rng));

        return map;
    }

};