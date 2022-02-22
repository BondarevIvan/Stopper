#pragma once
#include <GL/glut.h>

#include <geometry/Common.h>

namespace visualizer {
    struct Color {
        double red;
        double green;
        double blue;
        double alpha;
    };
    void draw_polygon(const geometry::Polygon2d& polygon, const Color& color, double pose_z = 0.0);
    void draw_polyline(const geometry::Polyline2d& polyline, const Color& color, double pose_z = 0.0);
    Color make_color(double red, double green, double blue, double alpha = 1.0);
}