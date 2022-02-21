#pragma once
#include <geometry/Common.h>
#include <sstream>

namespace hdmap {
    using UUID = unsigned long long;
    enum class Coordinates : int {
        Longitude = 0,
        Latitude = 1
    };
    class Node {
    public:
        Node() = delete;
        Node(UUID id, const geometry::Vector2d& coordinate);
        inline UUID id() const { 
            return id_; 
        }
        inline const geometry::Vector2d& coordinate() const { 
            return coordinate_; 
        }
        inline double latitude() const { 
            return coordinate_.get<static_cast<int>(Coordinates::Latitude)>(); 
        }
        inline double longitude() const { 
            return coordinate_.get<static_cast<int>(Coordinates::Longitude)>(); 
        }
    private:
        UUID id_;
        geometry::Vector2d coordinate_;
    };

    std::ostream& operator<<(std::ostream& out, const Node& node);
}