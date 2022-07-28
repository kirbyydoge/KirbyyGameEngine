#pragma once

class VertexBuffer {
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	void bind();
	void unbind();
private:
	unsigned int id;
};