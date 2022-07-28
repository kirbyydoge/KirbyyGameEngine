#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray() {
	glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &id);
}

void VertexArray::bind() const {
	glBindVertexArray(id);
}

void VertexArray::unbind() const {
	glBindVertexArray(0); 
}

void VertexArray::add_buffer(const VertexBuffer& vb, const VertexBufferAttributes& vattr) {
	bind();
	vb.bind();
	const auto& elements = vattr.get_elements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& elem = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, elem.count, elem.type, elem.normalized, vattr.get_stride(), (const void*) offset);
		offset += elem.count * elem.size;
	}
}
