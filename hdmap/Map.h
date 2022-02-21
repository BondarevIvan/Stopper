#pragma once
#include "Way.h"

#include <unordered_map>

namespace hdmap {
    class Map {
    public:
        Map(const std::string& filename);
        Map(const std::unordered_map<UUID, Node>& nodes,
            const std::unordered_map<UUID, Way>& ways);
        inline const std::unordered_map<UUID, Node>& nodes() const { return nodes_; }
        inline const std::unordered_map<UUID, Way>& ways() const { return ways_; }
    private:
        std::unordered_map<UUID, Node> nodes_;
        std::unordered_map<UUID, Way> ways_;
    };
}