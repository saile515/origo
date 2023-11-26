#pragma once

#include <vector>

namespace origo {

template<typename T>
class Buffer {
private:
    unsigned int _buffer_id;

public:
    Buffer();
    int set(std::vector<T> data);
    int bind_data(unsigned int attribute_id, unsigned int size);
};

}
