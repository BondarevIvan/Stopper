#include "visualizer.h"

namespace visualizer {
    void draw_polygon(
        const geometry::Polygon2d& polygon, const Color& color, double pose_z) {
        glBegin(GL_LINE_LOOP);
        glColor4d(color.red, color.green, color.blue, color.alpha);
        for (const auto& point : polygon.outer()) {
            glVertex3d(point.get<0>(), point.get<1>(), pose_z);
        }
        glEnd();
    }

    void draw_polyline(const geometry::Polyline2d& polyline, const Color& color, double pose_z) {
        glBegin(GL_LINE_STRIP);
        glColor4d(color.red, color.green, color.blue, color.alpha);
        for (const auto& point : polyline) {
            glVertex3d(point.get<0>(), point.get<1>(), pose_z);
        }
        glEnd();
    }

    Color make_color(double red, double green, double blue, double alpha) {
        return Color{red, green, blue, alpha};
    }

}