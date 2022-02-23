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
            {half_scales.get<0>(), -half_scales.get<1>()},
            half_scales * -1.,
            {-half_scales.get<0>(), half_scales.get<1>()}
        };
        namespace trans = boost::geometry::strategy::transform;

        const auto local = geometry::make_polygon(points);
        trans::translate_transformer<double, 2, 2> translate(position_.get<0>(), position_.get<1>());
        trans::rotate_transformer<boost::geometry::radian, double, 2, 2> rotate(yaw_);

        geometry::Polygon2d rotated, translated;
        boost::geometry::transform(local, rotated, rotate);
        boost::geometry::transform(rotated, translated, translate);

        return translated;
    }

}