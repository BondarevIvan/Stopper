#include "Node.h"

namespace hdmap {
    Node::Node(UUID id, const geometry::Vector2d& coordinate)
        : id_(id)
        , coordinate_(coordinate)
    {
    }

    std::ostream& operator<<(std::ostream& out, const Node& node) {
        return  out << "id: " << node.id() 
                    << " longitude: " << node.longitude() 
                    << " latitude: " << node.latitude();
    }
}