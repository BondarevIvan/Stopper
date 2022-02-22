#include "Common.h"

namespace geometry {
    Polygon2d make_polygon(const std::vector<Vector2d>& points) {
        Polygon2d result;
        for (const auto& point : points)
            bg::append(result, static_cast<bg::model::point<double, 2, bg::cs::cartesian>>(point));
        return result;
    }

    Polyline2d make_polyline(const std::vector<Vector2d>& points) {
        Polyline2d polyline;
        polyline.reserve(points.size());
        for (const auto& point : points)
            polyline.push_back(static_cast<bg::model::point<double, 2, bg::cs::cartesian>>(point));
        return polyline;
    }

    Vector2d::Vector2d()
        : Base{} 
        {
        }

    Vector2d::Vector2d(double x, double y)
        : Base(x, y)
    {
    }


    Vector2d& Vector2d::operator+=(const Vector2d& other) {
        set<0>(get<0>() + other.get<0>());
        set<1>(get<1>() + other.get<1>());
        return *this;
    }
    Vector2d& Vector2d::operator-=(const Vector2d& other) {
        set<0>(get<0>() - other.get<0>());
        set<1>(get<1>() - other.get<1>());
        return *this;
    }
    Vector2d& Vector2d::operator*=(double coef) {
        set<0>(get<0>() * coef);
        set<1>(get<1>() * coef);
        return *this;
    }
    Vector2d& Vector2d::operator/=(double coef) {
        return *this *= (1.0 / coef);
    }

    Vector2d Vector2d::operator+(const Vector2d& other) const {
        return Vector2d(*this) += other;
    }
    Vector2d Vector2d::operator-(const Vector2d& other) const {
        return Vector2d(*this) -= other;
    }
    Vector2d Vector2d::operator*(double coef) const {
        return Vector2d(*this) *= coef;
    }
    Vector2d Vector2d::operator/(double coef) const {
        return Vector2d(*this) /= coef;
    }

}