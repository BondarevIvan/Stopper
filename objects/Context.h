#pragma once
#include "Object.h"

namespace objects {
    class Context {
    public:
        Context() = default;
        Context(const std::vector<Object>& objects);
        inline const std::vector<Object>& objects() const { return objects_; }
        std::vector<Detection> object_at_time(double time) const;
    private:
        std::vector<Object> objects_{};
    };
}