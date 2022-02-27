#include "Common.h"

namespace geometry {
    Polygon2d make_polygon(const std::vector<Vector2d>& points) {
        Polygon2d result;
        for (const auto& point : points)
            bg::append(result, point);
        return result;
    }

    Polyline2d make_polyline(const std::vector<Vector2d>& points) {
        Polyline2d polyline;
        polyline.reserve(points.size());
        for (const auto& point : points)
            polyline.push_back(point);
        return polyline;
    }

    Vector2d get_position_on_polyline(
        const Polyline2d& polyline, const PolylinePoint& pp) {
        return polyline[pp.first] + 
            (polyline[pp.first + 1] - polyline[pp.first]) * pp.second;
    }

    double compute_length(const Polyline2d& polyline) {
        return boost::geometry::length(polyline);
    }

    boost::optional<PolylinePoint> walk_along_polyline(const Polyline2d& polyline, double dist) {
        if (polyline.size() < 2) {
            return {};
        }
        if (dist < 0) {
            return {};
        }
        for (int idx = 1; idx < static_cast<int>(polyline.size()); ++idx) {
            const double segment_length = (Vector2d(polyline[idx - 1]) - 
                                           Vector2d(polyline[idx])).norm();
            if (dist < segment_length) {
                return PolylinePoint{idx - 1, dist / segment_length};
            }
            dist -= segment_length;
        }
        return {};
    }

}