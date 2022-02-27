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

    Vector2d::Vector2d(const Base& base)
        : Base(base)
    {
    }


    Vector2d& Vector2d::operator+=(const Vector2d& other) {
        set<0>(x() + other.x());
        set<1>(y() + other.y());
        return *this;
    }
    Vector2d& Vector2d::operator-=(const Vector2d& other) {
        set<0>(x() - other.x());
        set<1>(y() - other.y());
        return *this;
    }
    Vector2d& Vector2d::operator*=(double coef) {
        set<0>(x() * coef);
        set<1>(y() * coef);
        return *this;
    }
    Vector2d& Vector2d::operator/=(double coef) {
        return *this *= (1.0 / coef);
    }

    double Vector2d::x() const {
        return get<0>();
    }
    double Vector2d::y() const {
        return get<1>
        ();
    }


    double Vector2d::dot(const Vector2d& other) const {
        return x() * other.x() + y() * other.y();
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
    double Vector2d::squared_norm() const {
        return std::sqrt(dot(*this));
    }
    double Vector2d::norm() const {
        return std::sqrt(squared_norm());
    }

    Vector2d get_position_on_polyline(
        const Polyline2d& polyline, const PolylinePoint& pp) {
        return Vector2d(polyline[pp.first]) + 
            (Vector2d(polyline[pp.first + 1]) - Vector2d(polyline[pp.first])) * pp.second;
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