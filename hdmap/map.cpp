#include "map.h"
#include <boost/property_tree/json_parser.hpp>

#include <logger/logger.h>

namespace hdmap {
    Map::Map(const std::string& filename) {
        std::ifstream file(filename);
        boost::property_tree::ptree map_data;
        boost::property_tree::json_parser::read_json(file, map_data);
        file.close();
        for (const auto& way_data : map_data.get_child("ways")) {
            Way way;
            parse_way(way_data.second, way);
            assert(way.id);
            ways_[*way.id] = way; 
        }
        for (const auto& node_data : map_data.get_child("nodes")) {
            Node node;
            parse_node(node_data.second, node);
            nodes_[node.id] = node;
        }
        LOG_EVENT("map success readed");
    }
    Map::Map(const std::unordered_map<UUID, Node>& nodes,
             const std::unordered_map<UUID, Way>& ways)
        : nodes_(nodes)
        , ways_(ways)
    {
    }
}