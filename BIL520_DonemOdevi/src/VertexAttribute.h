#pragma once

#include <vector>

struct vba_elem_t {
	unsigned int type;
	unsigned int count;
	unsigned int normalized;
	unsigned int size;
};

class VertexBufferAttributes {
public:
	VertexBufferAttributes();
	~VertexBufferAttributes();
	template<typename T> void push(unsigned int count);
	const std::vector<vba_elem_t>& get_elements() const;
	unsigned int get_stride() const;
private:
	unsigned int stride;
	std::vector<vba_elem_t> elements;
};