#include "object.h"

#include <logger/logger.h>

namespace objects {
    Object::Object(const ObjectHistory& history, UUID id, ObjectType type)
        : history_(history)
        , id_(id)
        , type_(type)
    {
    }

    geometry::Vector2d velocity_object(const Object& object) {
        if (object.velocity())
            return *object.velocity();
        const auto& history = object.history();
        if (history.size() < 2)
            return {};
        return history[history.size() - 1].position() - history[history.size() - 2].position();
    }

    boost::optional<Detection> Object::calculate_detection(double time) const {
        if (history_.size() < 2)
            return {};
        if (time > history_.front().timestamp())
            return {};
        if (time < history_.back().timestamp())
            return {};
        size_t l = 0, r = history_.size() - 2;
        while (r - l > 1) {
            const auto m = (l + r) >> 1;
            if (history_[m].timestamp() <= time) {
                r = m;
            } else {
                l = m;
            }
        }
        size_t idx = r;
        if (l > 0 && history_[l].timestamp() <= time) {
            idx = l;
        }
        const double coef = (time - history_[idx].timestamp()) 
        / //-------------------------------------------------------------------
                (history_[idx - 1].timestamp() - history_[idx].timestamp());
        geometry::Vector2d pos = geometry::lerp(
            history_[idx].position(), history_[idx - 1].position(), coef);
        const double yaw = geometry::lerp(
            history_[idx].yaw(), history_[idx - 1].yaw(), coef);
        return Detection(pos, history_.front().scales(), yaw, time, id_);
    }

    geometry::Vector2d acceleration_object(const Object& object) {
        if (object.acceleration())
            return *object.acceleration();
        return {};
    }
}