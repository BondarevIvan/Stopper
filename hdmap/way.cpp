#include "way.h"

#include <logger/logger.h>

namespace hdmap {
    void parse_way(const boost::property_tree::ptree& tree, Way& way) {
        way.id = tree.get_optional<UUID>("id");
        way.name = tree.get_optional<std::string>("name");
        way.surface = tree.get_optional<std::string>("surface");
        way.max_speed = tree.get_optional<double>("max_speed");
        way.role = tree.get_optional<std::string>("role");
        for (const auto& id : tree.get_child("node_ids")) {
            way.node_ids.push_back(boost::lexical_cast<UUID>(id.second.data()));
        }
    }
}