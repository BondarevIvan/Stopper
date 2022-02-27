#include "context.h"

#include <logger/logger.h>

namespace objects {

    Context::Context(const std::vector<Object>& objects)
        : objects_(objects)
    {
    }

    std::vector<Detection> Context::object_at_time(double time) const {
        std::vector<Detection> detections;
        detections.reserve(objects_.size());
        for (const auto& object : objects_) {
            const auto detection = object.calculate_detection(time);
            if (detection)
                detections.push_back(*detection);
        }
        detections.shrink_to_fit();
        return detections;
    }

}