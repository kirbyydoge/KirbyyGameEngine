#include "Mesh2D.h"
#include "Camera.h"

Mesh2D::Mesh2D() {
	sh = new Shader("res/shaders/mesh2dvshader.glsl", "res/shaders/mesh2dfshader.glsl");
	va = new VertexArray;
	vb = new VertexBuffer(nullptr, 0);
	ib = new IndexBuffer(nullptr, 0);
	VertexBufferAttributes vba;
	vba.push<float>(2);
	va->add_buffer(*vb, vba);
}

Mesh2D::~Mesh2D() {
	delete sh;
	delete va;
	delete vb;
	delete ib;
}

void Mesh2D::set_data(const float* data, unsigned int bytes) {
	vb->set_data(data, bytes);
}

void Mesh2D::set_index(unsigned int* indices, int count) {
	ib->set_indices(indices, count);
}

void Mesh2D::draw() const {
	bind();
	glDrawElements(GL_TRIANGLES, ib->get_count(), GL_UNSIGNED_INT, nullptr);
}

void Mesh2D::bind() const {
	sh->use();
	sh->set_uniform_matrix("u_model_proj", Camera::proj);
	va->bind();
	ib->bind();
}

void Mesh2D::unbind() const {
	sh->release();
	va->unbind();
	ib->unbind();
}

