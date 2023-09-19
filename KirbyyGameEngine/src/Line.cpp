#include "Line.h"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Camera.h"

Line::Line() {
	sh = new Shader("res/shaders/linevshader.glsl", "res/shaders/linefshader.glsl");
	va = new VertexArray;
	vb = new VertexBuffer(nullptr, sizeof(float) * 4);
	unsigned int idx_buf[] = { 0, 1 };
	ib = new IndexBuffer(idx_buf, 2);
	VertexBufferAttributes vba;
	int ibuffer[2] = { 0, 1 };
	vba.push<float>(2);
	va->add_buffer(*vb, vba);
}

Line::~Line() {
	delete sh;
	delete va;
	delete vb;
	delete ib;
}

void Line::set_pos(const glm::vec3 start, const glm::vec3 end) {
	float vbuffer[] = { start.x, start.y, end.x, end.y };
	vb->set_data(vbuffer, sizeof(float) * 4);
}

void Line::draw() const {
	bind();
	glDrawElements(GL_LINES, ib->get_count(), GL_UNSIGNED_INT, nullptr);
}

void Line::bind() const {
	sh->use();
	sh->set_uniform_matrix("u_model_proj", Camera::proj);
	va->bind();
	ib->bind();
}

void Line::unbind() const {
	va->unbind();
	ib->unbind();
}
