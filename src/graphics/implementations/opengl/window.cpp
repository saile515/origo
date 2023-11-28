#include "origo/graphics/window.hpp"

#include "GL/gl3w.h"
#include <GLFW/glfw3.h>

origo::Window::Window(int width, int height, std::string title)
  : _width(width)
  , _height(height)
  , _title(title){};

int origo::Window::open() {
    // GLFW setup

    if (!glfwInit()) {
        return 1;
    }

    _implementation_data.glfw_window =
        glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);

    if (!_implementation_data.glfw_window) {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(_implementation_data.glfw_window);

    // GL3W setup

    if (gl3wInit()) {
        return 1;
    }

    // OpenGL version 4.6
    if (!gl3wIsSupported(4, 6)) {
        return 1;
    }

    GLuint vertex_array_id;
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    return 0;
}

int origo::Window::close() {
    glfwDestroyWindow(_implementation_data.glfw_window);

    return 0;
}

int origo::Window::render() {
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(_implementation_data.glfw_window);
    glfwPollEvents();

    return 0;
}

bool origo::Window::should_update() {
    return !glfwWindowShouldClose(_implementation_data.glfw_window);
}
