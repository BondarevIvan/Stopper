#pragma once
#include <geometry/common.h>
#include <deque>

namespace objects {
    using UUID = unsigned long long;
    class Detection {
    public:
        Detection(
            const geometry::Vector2d& position, const geometry::Vector2d& scales, 
            double yaw, double timestamp, UUID id);
        inline const geometry::Vector2d& position() const { return position_; }
        inline const geometry::Vector2d& scales() const { return scales_; }
        inline double yaw() const { return yaw_; }
        inline double timestamp() const { return timestamp_; }
        inline UUID id() const { return id_; }
        geometry::Polygon2d polygon() const;
    private:
        UUID id_;
        geometry::Vector2d position_;
        geometry::Vector2d scales_;
        double yaw_;
        double timestamp_;
    };

    using ObjectHistory = std::deque<Detection>;
}