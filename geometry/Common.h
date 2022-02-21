#pragma once
#include <boost/geometry.hpp>
#include <vector>

namespace geometry {
    namespace bg = boost::geometry;
    using Vector2d = bg::model::point<double, 2, bg::cs::cartesian>;
    using Polygon2d = bg::model::polygon<Vector2d>;

    Polygon2d make_polygon(const std::vector<Vector2d>& points);
}