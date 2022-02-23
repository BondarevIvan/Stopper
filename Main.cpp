#include <logger/Logger.h>
#include <geometry/Common.h>
#include <hdmap/Map.h>
#include <visualizer/visualizer.h>
#include <visualizer/controller.h>
#include <objects/Context.h>

#include <cmath>

namespace {
    const double scaling_param = 1113;
    const geometry::Vector2d center{28.333511, 57.817074};

    hdmap::Map& get_local_map() {
        static hdmap::Map local_map(logger::root_folder() + "/map.json");
        return local_map;
    }

    void display() {
        glClear(GL_COLOR_BUFFER_BIT);
        const auto& ways = get_local_map().ways();
        for (const auto& way_data : ways) {
            visualizer::visualize_way(get_local_map(), way_data.second);
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
    visualizer::scaling(scaling_param);
    visualizer::translate(center * -1.0);
    glutDisplayFunc(display);

    glutMotionFunc(visualizer::motion_mouse_function);
    glutPassiveMotionFunc(visualizer::mouse_passive);
    glutTimerFunc(50, timer, 0);
    glutMainLoop();

    LOG_EVENT("end");
    return 0;
}