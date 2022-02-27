#include "visualizer.h"

#include <logger/logger.h>

namespace visualizer {
    const double x = 28.333511, y = 57.817074;
    const geometry::Vector2d center(x, y);

    void draw_polygon(
        const geometry::Polygon2d& polygon, const Color& color, double pose_z) {
        glBegin(GL_LINE_LOOP);
        glColor4d(color.red, color.green, color.blue, color.alpha);
        for (const auto& point : polygon.outer()) {
            glVertex3d(point.x(), point.y(), pose_z);
        }
        glEnd();
    }

    void draw_polyline(const geometry::Polyline2d& polyline, const Color& color, double pose_z) {
        glBegin(GL_LINE_STRIP);
        glColor4d(color.red, color.green, color.blue, color.alpha);
        for (const auto& point : polyline) {
            glVertex3d(point.x(), point.y(), pose_z);
        }
        glEnd();
    }

    void visualize_way(const hdmap::Map& local_map, const hdmap::Way& way) {
        Color color = make_color(1.0, 1.0, 0.0);
        if (!way.surface)
            color = make_color(1.0, 1.0, 1.0);
        else if (*way.surface == "asphalt") {
            color = make_color(0.0, 1.0, 0.0);
        }
        else if (*way.surface == "paving_stones") {
            color = make_color(1.0, 0.0, 0.0);
        }
        else if (*way.surface == "gravel") {
            color = make_color(0, 0, 1.0);
        }
        const auto& nodes = local_map.nodes();
        std::vector<geometry::Vector2d> points;
        for (const auto& node_id : way.node_ids) {
            const auto& node = nodes.at(node_id);
            points.push_back(node.position);
        }
        draw_polyline(geometry::make_polyline(points), color);
    }

    void visualize_object(const objects::Detection& detection) {
        draw_polygon(detection.polygon(), make_color(0.9, 0.9, 0.1));
    }

    Color make_color(double red, double green, double blue, double alpha) {
        Color col;
        col.red = red;
        col.green = green;
        col.blue = blue;
        col.alpha = alpha;
        return col;
    }

}