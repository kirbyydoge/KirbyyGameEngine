#pragma once

class IndexBuffer {
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();
	void set_indices(const unsigned int* data, unsigned int count);
	void bind() const;
	void unbind() const;
	unsigned int get_count() const;
private:
	unsigned int id;
	unsigned int count;
};