#include "graphics/buffer.hpp"

#include "GL/gl3w.h"

template class origo::Buffer<char>;
template class origo::Buffer<unsigned char>;
template class origo::Buffer<short>;
template class origo::Buffer<unsigned short>;
template class origo::Buffer<int>;
template class origo::Buffer<unsigned int>;
template class origo::Buffer<float>;
template class origo::Buffer<double>;

template<typename T>
origo::Buffer<T>::Buffer() {
    GLuint buffer_id;
    glGenBuffers(1, &buffer_id);
    _buffer_id = buffer_id;
}

template<typename T>
int origo::Buffer<T>::set(std::vector<T> data) {
    glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
    glBufferData(GL_ARRAY_BUFFER, data.size(), &data[0], GL_STATIC_DRAW);

    return 0;
}

template<typename T>
int origo::Buffer<T>::bind_data(unsigned int attribute_id, unsigned int size) {
    glEnableVertexAttribArray(attribute_id);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);

    GLenum type;

    if (std::is_same<T, char>::value) {
        type = GL_BYTE;
    } else if (std::is_same<T, unsigned char>::value) {
        type = GL_UNSIGNED_BYTE;
    } else if (std::is_same<T, short>::value) {
        type = GL_SHORT;
    } else if (std::is_same<T, unsigned short>::value) {
        type = GL_UNSIGNED_SHORT;
    } else if (std::is_same<T, int>::value) {
        type = GL_INT;
    } else if (std::is_same<T, unsigned int>::value) {
        type = GL_UNSIGNED_INT;
    } else if (std::is_same<T, float>::value) {
        type = GL_FLOAT;
    } else if (std::is_same<T, double>::value) {
        type = GL_DOUBLE;
    }

    glVertexAttribPointer(
        attribute_id, size, type, GL_FALSE, 0, static_cast<void*>(0));

    return 0;
}
