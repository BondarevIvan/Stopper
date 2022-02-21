#include "Common.h"

namespace geometry {
    Polygon2d make_polygon(const std::vector<Vector2d>& points) {
        Polygon2d result;
        for (const auto& point : points)
            bg::append(result, point);
        return result;
    }

}