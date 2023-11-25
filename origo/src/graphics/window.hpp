#pragma once

#include "doctest/doctest.h"
#include <chrono>
#include <string>
#include <thread>

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
    int clear();
    int render();
    bool should_update();
};
}

TEST_CASE("Window test") {
    origo::Window window(640, 480, "Test Window");

    REQUIRE(window.open() == 0);

    std::this_thread::sleep_for(std::chrono::milliseconds(10000));

    CHECK(window.close() == 0);
}
