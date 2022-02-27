#pragma once
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>

namespace geometry {
    namespace bg = boost::geometry;
    class Vector2d {
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

        double& x();
        double& y();

        double dot(const Vector2d& other) const;

        double squared_norm() const;
        double norm() const;
    private:
        double x_;
        double y_;
    };
}

using geometry::Vector2d;
BOOST_GEOMETRY_REGISTER_POINT_2D(Vector2d, double, boost::geometry::cs::cartesian, x(), y())
