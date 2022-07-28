#pragma once

#include "VertexBuffer.h"
#include "VertexAttribute.h"

class VertexArray {
public:
	VertexArray();
	~VertexArray();
	void bind() const;
	void unbind() const;
	void add_buffer(const VertexBuffer& vb, const VertexBufferAttributes& vba);
private:
	unsigned int id;
};