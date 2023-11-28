#include "origo/graphics/shader.hpp"

#include "util/files.hpp"
#include <GL/gl3w.h>
#include <fstream>
#include <sstream>

origo::Shader::Shader() {}

int origo::Shader::load_shader(std::string vertex_path,
                               std::string fragment_path) {
    unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    std::optional<std::string> vertex_source =
        origo::util::read_file(vertex_path);
    std::optional<std::string> fragment_source =
        origo::util::read_file(fragment_path);

    if (!vertex_source.has_value() || !fragment_source.has_value()) {
        return 1;
    }

    return 0;
}
