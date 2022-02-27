#pragma once
#include <geometry/common.h>

namespace visualizer {
    static const int WidthScreen = 800;
    static const int HeightScreen = 800;
    void rotate(double angle);
    void translate(const geometry::Vector2d& direction);
    void scaling(double param);
    void motion_mouse_function(int x, int y);
    void mouse_passive(int x, int y);
}