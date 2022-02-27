#include <logger/logger.h>
#include <geometry/common.h>
#include <hdmap/map.h>
#include <visualizer/visualizer.h>
#include <visualizer/controller.h>
#include <objects/context.h>

#include <cmath>

namespace {
    hdmap::Map& get_local_map() {
        static hdmap::Map local_map(logger::root_folder() + "/map.json");
        return local_map;
    }

    geometry::Polyline2d get_way_line(const hdmap::Way& way) {
        std::vector<geometry::Vector2d> points;
        const auto& local_map = get_local_map();
        points.reserve(way.node_ids.size());
        for (const auto& node_id : way.node_ids) {
            const auto& node = local_map.nodes().at(node_id);
            points.push_back(node.position);
        }
        return geometry::make_polyline(points);
    }

    const double scaling_param = 1113;
    const geometry::Vector2d center{28.333530, 57.817060};
    const double speed = 50.0;
    double timestamp = 0.0;

    const hdmap::Way& get_nearest_way(const geometry::Vector2d& point) {
        auto& ways = get_local_map().ways();
        hdmap::Way* way_best = nullptr;
        double dist_best = std::numeric_limits<double>::infinity();
        for (auto& way_data : ways) {
            auto& way = way_data.second;
            if (!way.surface || *way.surface != "asphalt")
                continue;
            const auto current_dist = boost::geometry::distance(get_way_line(way), point);
            if (!way_best || current_dist < dist_best) {
                way_best = &way;
                dist_best = current_dist;
            }
        }
        return *way_best;
    }

    objects::Context& get_context() {
        const auto make_centerline_moving = [](
            const hdmap::Way& way, double width, double height, 
            double velocity, double bias, int num_steps, double step_duration, objects::UUID id) {
            const auto polyline = get_way_line(way);
            objects::ObjectHistory history;
            for (int idx = 0; idx < num_steps; ++idx) {
                const double time = idx * step_duration;
                const auto walk = geometry::walk_along_polyline(polyline, time * velocity + bias);
                if (!walk)
                    break;
                history.emplace_back(
                    geometry::get_position_on_polyline(polyline, *walk), 
                    geometry::Vector2d{width, height}, 
                    0.0, time, id);
            }
            std::reverse(history.begin(), history.end());
            return objects::Object(history, id, objects::ObjectType::PassengerCar);
        };

        const auto make_context_objects = [&]() -> std::vector<objects::Object> {
            const auto& way = get_nearest_way(center);
            const double width = 1e-5 * 5, height = 1e-4;
            const double velocity = 1e-2;
            const int num_step = 15;
            const double step_duration = 0.5;
            return {
                make_centerline_moving(way, width, height, velocity, (height + width) * 0.0, num_step, step_duration, 1),
                make_centerline_moving(way, width, height, velocity, (height + width) * 1.0, num_step, step_duration, 2),
                make_centerline_moving(way, width, height, velocity, (height + width) * 2.0, num_step, step_duration, 3),
                make_centerline_moving(way, width, height, velocity, (height + width) * 3.0, num_step, step_duration, 4),
            };
        };
        static objects::Context context(make_context_objects());
        return context;
    }

    const double millisecond_to_seconds(double milliseconds) {
        return milliseconds / 1000.0;
    }

    void display() {
        glClear(GL_COLOR_BUFFER_BIT);
        const auto& ways = get_local_map().ways();
        for (const auto& way_data : ways) {
            visualizer::visualize_way(get_local_map(), way_data.second);
        }
        for (const auto object : get_context().object_at_time(timestamp)) {
            visualizer::visualize_object(object);
        }
        glutSwapBuffers();
    }

    void timer(int) {
        display();
        timestamp += 1. / speed;
        glutTimerFunc(speed, timer, 0);
    }
}

int main(int argc, char** argv) {
    LOG_EVENT("begin");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutInitWindowSize(visualizer::WidthScreen, visualizer::HeightScreen);
    glutCreateWindow("Test");
    visualizer::scaling(scaling_param);
    visualizer::translate(center * -1.0);
    glutDisplayFunc(display);

    glutMotionFunc(visualizer::motion_mouse_function);
    glutPassiveMotionFunc(visualizer::mouse_passive);
    glutTimerFunc(speed, timer, 0);
    glutMainLoop();

    LOG_EVENT("end");
    return 0;
}