#include "Way.h"

namespace hdmap {
    Way::Way(UUID id,
             const std::vector<UUID>& node_ids, 
             const std::string& name, 
             const std::string& surface, 
             double max_speed, 
             bool one_way) 
        : id_(id)
        , node_ids_(node_ids)
        , name_(name)
        , surface_(surface)
        , max_speed_(max_speed)
        , one_way_(one_way)
    {
    }

    std::ostream& operator<<(std::ostream& out, const Way& way) {
        return  out << "id: " << way.id()
                    << " name:" << way.name()
                    << " surface: " << way.surface()
                    << " max speed: " << way.max_speed()
                    << " one way: " << way.one_way();
    }
}