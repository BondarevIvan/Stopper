#include "Node.h"

namespace hdmap {
    void parse_node(const boost::property_tree::ptree& tree, Node& node) {
        node.id = tree.get<UUID>("id", 0);
        node.position.x() = tree.get<double>("lon");
        node.position.y() = tree.get<double>("lat");
    }
}