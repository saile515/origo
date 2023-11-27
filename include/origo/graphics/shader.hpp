#pragma once

#include <string>

namespace origo {

class Shader {
private:
    unsigned int _shader_id;

public:
    Shader();
    int load_shader(std::string vertex_path, std::string fragment_path);
    int use_shader();
};

}
