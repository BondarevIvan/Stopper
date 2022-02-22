#include <logger/Logger.h>
#include <geometry/Common.h>
#include <hdmap/Map.h>
#include <visualizer/visualizer.h>

namespace {
    hdmap::Map& get_local_map() {
        static hdmap::Map local_map(logger::root_folder() + "/map.json");
        return local_map;
    }

    double x = 37.530930, y = 55.702987;
    const geometry::Vector2d center{x, y};

    void display() {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        const auto& nodes = get_local_map().nodes();
        const auto& ways = get_local_map().ways();
        const auto way_polyline = [&](const hdmap::Way& way) {
            geometry::Polyline2d polyline;
            polyline.reserve(way.node_ids.size());
            for (const auto& node_id : way.node_ids) {
                const auto& node = nodes.at(node_id);
                const double scale = 1113.2;
                polyline.push_back(geometry::Vector2d{
                    (node.position.get<0>() - center.get<0>()) * scale, 
                    (node.position.get<1>() - center.get<1>()) * scale});
            }
            return polyline;
        };
        for (const auto& [uuid, way] : ways) {
            visualizer::draw_polyline(way_polyline(way), visualizer::make_color(1.0, 1.0, 1.0));
        }
        glutSwapBuffers();
    }
}

int main(int argc, char** argv) {
    LOG_EVENT("begin");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 800);
    //glTranslated(-y, -x, 0.0);
    glutCreateWindow("Test");
    glutDisplayFunc(display);
    glutMainLoop();
    LOG_EVENT("end");
    return 0;
}