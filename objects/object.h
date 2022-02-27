#pragma once
#include "detection.h"
#include <boost/optional/optional.hpp>

namespace objects {
    enum ObjectType {
        Pedestrian,
        Cyclist,
        Bus,
        PassengerCar,
        Truck
    };
    class Object {
    public:
        Object(const ObjectHistory& history, UUID id, ObjectType type);
        inline const ObjectHistory& history() const { return history_; }
        inline UUID id() const { return id_; }
        inline ObjectType type() const { return type_; }
        inline boost::optional<geometry::Vector2d>& velocity() { return velocity_; }
        inline boost::optional<geometry::Vector2d>& acceleration() { return acceleration_; }
        inline const boost::optional<geometry::Vector2d>& velocity() const { return velocity_; }
        inline const boost::optional<geometry::Vector2d>& acceleration() const { return acceleration_; }
        boost::optional<Detection> calculate_detection(double time) const;
    private:
        ObjectHistory history_;
        UUID id_;
        ObjectType type_;
        boost::optional<geometry::Vector2d> velocity_;
        boost::optional<geometry::Vector2d> acceleration_;
    };

    geometry::Vector2d velocity_object(const Object& object);

    geometry::Vector2d acceleration_object(const Object& object);
}