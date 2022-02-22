#pragma once
#include <geometry/Common.h>
#include <boost/property_tree/ptree.hpp>
#include <sstream>

namespace hdmap {
    using UUID = unsigned long long;
    enum class Coordinates : int {
        Longitude = 0,
        Latitude = 1
    };

    struct Node {
        UUID id;
        geometry::Vector2d position;
    };

    void parse_node(const boost::property_tree::ptree& tree, Node& node);
}