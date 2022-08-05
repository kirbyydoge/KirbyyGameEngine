#pragma once
#include "RenderableComponent.h"
#include "glm/glm.hpp"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Line : public RenderableComponent {
public:
	Line();
	~Line();
	virtual void draw() const;
	void set_pos(const glm::vec3 start, const glm::vec3 end);
	void bind() const;
	void unbind() const;
private:
	Shader* sh;
	VertexArray* va;
	VertexBuffer* vb;
	IndexBuffer* ib;
	unsigned int id;
};