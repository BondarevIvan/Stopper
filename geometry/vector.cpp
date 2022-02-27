#include "vector.h"

namespace geometry {
    Vector2d::Vector2d()
        : x_{}, y_{} 
    {
    }

    Vector2d::Vector2d(double x, double y)
        : x_(x), y_(y)
    {
    }

    Vector2d& Vector2d::operator+=(const Vector2d& other) {
        x_ = (x() + other.x());
        y_ = (y() + other.y());
        return *this;
    }
    Vector2d& Vector2d::operator-=(const Vector2d& other) {
        x_ = (x() - other.x());
        y_ = (y() - other.y());
        return *this;
    }
    Vector2d& Vector2d::operator*=(double coef) {
        x_ = (x() * coef);
        y_ = (y() * coef);
        return *this;
    }
    Vector2d& Vector2d::operator/=(double coef) {
        return *this *= (1.0 / coef);
    }

    double Vector2d::x() const {
        return x_;
    }
    double Vector2d::y() const {
        return y_;
    }

    double& Vector2d::x() {
        return x_;
    }
    double& Vector2d::y() {
        return y_;
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

}