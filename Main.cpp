#include <logger/Logger.h>
#include <geometry/Common.h>
#include <hdmap/Map.h>
#include <visualizer/visualizer.h>
#include <visualizer/controller.h>

namespace {
    hdmap::Map& get_local_map() {
        static hdmap::Map local_map(logger::root_folder() + "/map.json");
        return local_map;
    }

    const double x = 37.530930, y = 55.702987;
    const geometry::Vector2d center(x, y);

    void display() {
        glClear(GL_COLOR_BUFFER_BIT);
        const auto& nodes = get_local_map().nodes();
        const auto& ways = get_local_map().ways();
        const auto way_polyline = [&](const hdmap::Way& way) {
            geometry::Polyline2d polyline;
            polyline.reserve(way.node_ids.size());
            for (const auto& node_id : way.node_ids) {
                const auto& node = nodes.at(node_id);
                const double scale = 1113.2;
                polyline.push_back((node.position - center) * scale);
            }
            return polyline;
        };
        for (const auto& [uuid, way] : ways) {
            visualizer::draw_polyline(way_polyline(way), visualizer::make_color(1.0, 1.0, 1.0));
        }
        glutSwapBuffers();
    }

    void timer(int) {
        display();
        glutTimerFunc(50, timer, 0);
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
    glutDisplayFunc(display);

    glutMotionFunc(visualizer::motion_mouse_function);
    glutPassiveMotionFunc(visualizer::mouse_passive);
    glutTimerFunc(50, timer, 0);
    glutMainLoop();

    LOG_EVENT("end");
    return 0;
}