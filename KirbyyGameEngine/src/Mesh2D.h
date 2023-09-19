#pragma once
#include "RenderableComponent.h"
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "glm/glm.hpp"

class Mesh2D : public RenderableComponent {
public:
	Mesh2D();
	~Mesh2D();
	virtual void draw() const;
	void set_data(const float* data, unsigned int bytes);
	void set_index(unsigned int* indices, int count);
	void bind() const;
	void unbind() const;
private:
	Shader* sh;
	VertexArray* va;
	VertexBuffer* vb;
	IndexBuffer* ib;
};