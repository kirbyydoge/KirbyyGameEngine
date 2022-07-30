#pragma once

class IndexBuffer {
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();
	void bind() const;
	void unbind() const;
	unsigned int get_count() const;
private:
	unsigned int id;
	unsigned int count;
};