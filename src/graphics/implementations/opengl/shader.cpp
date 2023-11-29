#include "origo/graphics/shader.hpp"

#include "util/files.hpp"
#include <GL/gl3w.h>
#include <fstream>
#include <sstream>

origo::Shader::Shader() {}

int origo::Shader::load(std::string vertex_path, std::string fragment_path) {
    unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    std::optional<std::string> vertex_source =
        origo::util::read_file(vertex_path);
    std::optional<std::string> fragment_source =
        origo::util::read_file(fragment_path);

    if (!vertex_source.has_value() || !fragment_source.has_value()) {
        return 1;
    }

    // Compile shader
    const char* vertex_source_c = vertex_source.value().c_str();
    glShaderSource(vertex_shader_id, 1, &vertex_source_c, NULL);
    glCompileShader(vertex_shader_id);

    // Check if shader compiled
    int vertex_result = GL_FALSE;
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &vertex_result);

    if (vertex_result != GL_TRUE) {
        return 1;
    };

    // ^^^
    const char* fragment_source_c = fragment_source.value().c_str();
    glShaderSource(fragment_shader_id, 1, &fragment_source_c, NULL);
    glCompileShader(fragment_shader_id);

    // ^^^
    int fragment_result = GL_FALSE;
    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &fragment_result);

    if (fragment_result != GL_TRUE) {
        return 1;
    };

    // Create shader program
    _shader_id = glCreateProgram();
    glAttachShader(_shader_id, vertex_shader_id);
    glAttachShader(_shader_id, fragment_shader_id);
    glLinkProgram(_shader_id);

    // Check if program linked
    int program_result = GL_FALSE;
    glGetProgramiv(_shader_id, GL_LINK_STATUS, &program_result);

    if (program_result != GL_TRUE) {
        return 1;
    }

    // Delete shaders
    glDetachShader(_shader_id, vertex_shader_id);
    glDetachShader(_shader_id, fragment_shader_id);
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return 0;
}

int origo::Shader::use() {
    glUseProgram(_shader_id);

    return 0;
}
