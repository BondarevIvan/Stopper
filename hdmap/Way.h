#pragma once
#include "Node.h"

#include <vector>
#include <string>

namespace hdmap {
    class Way {
    public:
        Way(UUID id,
            const std::vector<UUID>& node_ids, 
            const std::string& name, 
            const std::string& surface, 
            double max_speed, 
            bool one_way);
        inline UUID id() const { return id_; }
        inline const std::vector<UUID>& node_ids() const { return node_ids_; }
        inline const std::string& name() const { return name_; }
        inline const std::string& surface() const { return surface_; }
        inline double max_speed() const { return max_speed_; }
        inline bool one_way() const { return one_way_; }
    private:
        UUID id_;
        std::vector<UUID> node_ids_;
        std::string name_;
        std::string surface_;
        double max_speed_;
        bool one_way_;
    };

    std::ostream& operator<<(std::ostream& out, const Way& way);
}