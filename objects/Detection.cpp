#include "Detection.h"

namespace objects {
    Detection::Detection(
        const geometry::Vector2d& position, const geometry::Vector2d& scales, 
        double yaw, double timestamp, UUID id)
        : position_(position)
        , scales_(scales)
        , yaw_(yaw)
        , timestamp_(timestamp)
        , id_(id)
    {
    }

    geometry::Polygon2d Detection::polygon() const {
        const geometry::Vector2d half_scales = this->scales() / 2.0;
        std::vector<geometry::Vector2d> points = {
            half_scales,
            {half_scales.x(), -half_scales.y()},
            half_scales * -1.,
            {-half_scales.x(), half_scales.y()}
        };
        namespace trans = boost::geometry::strategy::transform;

        const auto local = geometry::make_polygon(points);
        trans::translate_transformer<double, 2, 2> translate(position_.x(), position_.y());
        trans::rotate_transformer<boost::geometry::radian, double, 2, 2> rotate(yaw_);

        geometry::Polygon2d rotated, translated;
        boost::geometry::transform(local, rotated, rotate);
        boost::geometry::transform(rotated, translated, translate);

        return translated;
    }

}