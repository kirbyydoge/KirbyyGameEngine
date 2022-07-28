#include "VertexAttribute.h"
#include <GL/glew.h>

VertexBufferAttributes::VertexBufferAttributes() {
	stride = 0;
}

VertexBufferAttributes::~VertexBufferAttributes() {}

const std::vector<vba_elem_t>& VertexBufferAttributes::get_elements() const {
	return elements;
}

unsigned int VertexBufferAttributes::get_stride() const {
	return stride;
}

template<typename T>
void VertexBufferAttributes::push(unsigned int count) {
	static_assert(false);
}

template<>
void VertexBufferAttributes::push<float>(unsigned int count) {
	elements.push_back({ GL_FLOAT, count, GL_FALSE , sizeof(GLfloat) });
	stride += sizeof(GLfloat) * count;
}

template<>
void VertexBufferAttributes::push<unsigned int>(unsigned int count) {
	elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE, sizeof(GLuint) });
	stride += sizeof(GLuint) * count;
}


template<>
void VertexBufferAttributes::push<unsigned char>(unsigned int count) {
	elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE, sizeof(GLbyte) });
	stride += sizeof(GLbyte) * count;
}
