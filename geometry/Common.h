#pragma once
#include <boost/geometry.hpp>
#include <boost/optional/optional.hpp>
#include <vector>

namespace geometry {
    namespace bg = boost::geometry;
    class Vector2d : public bg::model::point<double, 2, bg::cs::cartesian> {
    public:
        using Base = bg::model::point<double, 2, bg::cs::cartesian>;
        Vector2d();
        Vector2d(double x, double y);
        Vector2d(const Base& base);
        Vector2d& operator+=(const Vector2d& other);
        Vector2d& operator-=(const Vector2d& other);
        Vector2d& operator*=(double coef);
        Vector2d& operator/=(double coef);

        Vector2d operator+(const Vector2d& other) const;
        Vector2d operator-(const Vector2d& other) const;
        Vector2d operator*(double coef) const;
        Vector2d operator/(double coef) const;

        double x() const;
        double y() const;

        double dot(const Vector2d& other) const;

        double squared_norm() const;
        double norm() const;
    private:
    };

    using Polygon2d = bg::model::polygon<bg::model::point<double, 2, bg::cs::cartesian>>;
    using Polyline2d = bg::model::linestring<bg::model::point<double, 2, bg::cs::cartesian>>;

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