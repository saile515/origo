#pragma once

#include <vector>

namespace origo {

enum Attribute { vertex_position };

template<typename T>
class Buffer {
private:
    unsigned int _buffer_id;

public:
    Buffer();
    int set(std::vector<T> data);
    int bind_data(origo::Attribute attribute_id, int size);
};

}
