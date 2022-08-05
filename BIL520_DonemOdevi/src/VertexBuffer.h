#pragma once

class VertexBuffer {
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	void bind() const;
	void unbind() const;
	void set_data(const void* data, unsigned int size);
private:
	unsigned int id;
};