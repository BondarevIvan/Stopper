#pragma once
#include <boost/geometry.hpp>
#include <vector>

namespace geometry {
    namespace bg = boost::geometry;
    class Vector2d : public bg::model::point<double, 2, bg::cs::cartesian> {
    public:
        using Base = bg::model::point<double, 2, bg::cs::cartesian>;
        Vector2d();
        Vector2d(double x, double y);
        Vector2d& operator+=(const Vector2d& other);
        Vector2d& operator-=(const Vector2d& other);
        Vector2d& operator*=(double coef);
        Vector2d& operator/=(double coef);

        Vector2d operator+(const Vector2d& other) const;
        Vector2d operator-(const Vector2d& other) const;
        Vector2d operator*(double coef) const;
        Vector2d operator/(double coef) const;
    private:
    };

    using Polygon2d = bg::model::polygon<bg::model::point<double, 2, bg::cs::cartesian>>;
    using Polyline2d = bg::model::linestring<bg::model::point<double, 2, bg::cs::cartesian>>;

    Polygon2d make_polygon(const std::vector<Vector2d>& points);
    Polyline2d make_polyline(const std::vector<Vector2d>& points);
}