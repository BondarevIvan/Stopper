#include "Node.h"

namespace hdmap {
    void parse_node(const boost::property_tree::ptree& tree, Node& node) {
        node.id = tree.get<UUID>("id", 0);
        node.position.set<0>(tree.get<double>("lon"));
        node.position.set<1>(tree.get<double>("lat"));
    }
}