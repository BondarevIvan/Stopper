#include "controller.h"

#include <GL/glut.h>

#include <iostream>

namespace visualizer {
    struct CameraParams {
        double angle{};
        geometry::Vector2d center{};
        double scaling = 1.0;
    } camera_params;
    
    struct MouseState {
        int cursor_pos_x;
        int cursor_pos_y;
    } mouse_state;

    void rotate(double angle) {
        glRotated(angle - camera_params.angle, 0.0, 0.0, 1.0);
        camera_params.angle = angle;
    }

    void translate(const geometry::Vector2d& direction) {
        glTranslated(direction.get<0>(), direction.get<1>(), 0.0);
        camera_params.center += direction;
    }

    void scaling(double param) {
        glScaled(param / camera_params.scaling, param / camera_params.scaling, 1.0);
        camera_params.scaling = param;
    }

    void motion_mouse_function(int x, int y) {
        const double relative_x = static_cast<double>(x - mouse_state.cursor_pos_x) / WidthScreen;
        const double relative_y = -static_cast<double>(y - mouse_state.cursor_pos_y) / HeightScreen;        
        translate(geometry::Vector2d{relative_x, relative_y});
        mouse_passive(x, y);
    }

    void mouse_passive(int x, int y) {
        mouse_state.cursor_pos_x = x;
        mouse_state.cursor_pos_y = y;
    }

}