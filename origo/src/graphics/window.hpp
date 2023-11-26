#pragma once

#include <string>

#if GRAPHICS_IMPLENTATION == opengl
struct GLFWwindow;

struct ImplementationData {
    GLFWwindow* glfw_window;
};
#endif

namespace origo {

class Window {
private:
    int _width;
    int _height;
    std::string _title;
    ImplementationData _implementation_data;

public:
    Window(int width, int height, std::string title);

    int open();
    int close();
    int render();
    bool should_update();
};
}
