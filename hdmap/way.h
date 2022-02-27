#pragma once
#include "node.h"

#include <boost/optional/optional.hpp>
#include <vector>
#include <string>

namespace hdmap {
    struct Way {
        boost::optional<int> id;
        boost::optional<std::string> name;
        boost::optional<std::string> surface;
        boost::optional<std::string> role;
        std::vector<UUID> node_ids;
        boost::optional<double> max_speed;
    };

    void parse_way(const boost::property_tree::ptree& tree, Way& way);
}