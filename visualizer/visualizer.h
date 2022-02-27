#pragma once
#include <GL/glut.h>
#include <hdmap/map.h>
#include <geometry/common.h>
#include <objects/detection.h>

namespace visualizer {
    struct Color {
        double red{};
        double green{};
        double blue{};
        double alpha = 1.0;
    };
    void draw_polygon(const geometry::Polygon2d& polygon, const Color& color, double pose_z = 0.0);
    void draw_polyline(const geometry::Polyline2d& polyline, const Color& color, double pose_z = 0.0);
    Color make_color(double red, double green, double blue, double alpha = 1.0);
    void visualize_way(const hdmap::Map& local_map, const hdmap::Way& way);
    void visualize_object(const objects::Detection& detection);
}