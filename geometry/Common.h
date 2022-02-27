#pragma once
#include "Vector.h"

#include <boost/optional/optional.hpp>
#include <vector>

namespace geometry {

    using Polygon2d = bg::model::polygon<Vector2d>;
    using Polyline2d = bg::model::linestring<Vector2d>;

    using PolylinePoint = std::pair<int, double>;

    Polygon2d make_polygon(const std::vector<Vector2d>& points);
    Polyline2d make_polyline(const std::vector<Vector2d>& points);
    double compute_length(const Polyline2d& polyline);
    boost::optional<PolylinePoint> walk_along_polyline(const Polyline2d& polyline, double dist);

    Vector2d get_position_on_polyline(const Polyline2d& polyline, const PolylinePoint& pp);

    template<class T>
    T lerp(const T& start, const T& finish, double coef) {
        return start + (finish - start) * coef;
    }
}