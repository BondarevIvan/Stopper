#include "Map.h"
#include <boost/property_tree/json_parser.hpp>

namespace hdmap {
    Map::Map(const std::string& filename) {
        std::ifstream file(filename);
        boost::property_tree::ptree map_data;
        boost::property_tree::json_parser::read_json(file, map_data);
        file.close();
        const auto& ways = map_data.get_child("ways");
        for (const auto& way : ways) {
            const auto& way_data = way.second;
            UUID way_id = way_data.get<UUID>("id");
            std::vector<UUID> node_ids = way_data.get<std::vector<UUID>>("node_ids");
            std::string name = way_data.get<std::string>("name");
            std::string surface = way_data.get<std::string>("surface");
            double max_speed = way_data.get<double>("max_speed");
            bool one_way = way_data.get<bool>("one_way");
            ways_[way_id] = Way(way_id, node_ids, name, surface, max_speed, one_way);
        }
        const auto& nodes = map_data.get_child("nodes");
        for (const auto& node : nodes) {
            
        }
    }
    Map::Map(const std::unordered_map<UUID, Node>& nodes,
             const std::unordered_map<UUID, Way>& ways)
        : nodes_(nodes)
        , ways_(ways)
    {
    }
}