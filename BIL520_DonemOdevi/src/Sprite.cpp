#include "Sprite.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GameRenderer.h"
#include "GameObject.h"

Sprite::Sprite(unsigned int tex_count) {
	this->tex_count = tex_count;
	proj = nullptr;
	textures = new Texture[tex_count];
	shader = nullptr;
	va = nullptr;
	ib = nullptr;
	active_text = 0;
	active_slot = 0;
}

Sprite::~Sprite() {
	delete textures;
}

void Sprite::set_projection(glm::mat4* proj) {
	this->proj = proj;
}

void Sprite::set_shader(Shader* shader) {
	this->shader = shader;
}

Shader& Sprite::get_shader() {
	return *shader;
}

void Sprite::set_vertex_array(VertexArray* va) {
	this->va = va;
}

VertexArray& Sprite::get_vertex_array() {
	return *va;
}

void Sprite::set_index_buffer(IndexBuffer* ib) {
	this->ib = ib;
}

IndexBuffer& Sprite::get_index_buffer() {
	return *ib;
}

void Sprite::set_texture(const std::string& path, unsigned int tex_idx) {
	textures[tex_idx].change_tex(path);
}

Texture& Sprite::get_texture(unsigned int tex_idx) {
	return textures[tex_idx];
}

void Sprite::bind() const {
	glm::mat4 view = glm::translate(glm::mat4(1.0f), base->get_transform().get_pos());
	shader->use();
	shader->set_uniform<int>("u_texture", 0);
	shader->set_uniform_matrix<glm::mat4>("u_model_proj", *proj);
	shader->set_uniform_matrix<glm::mat4>("u_model_view", view);
	va->bind();
	ib->bind();
	textures[active_text].bind(active_slot);
}

void Sprite::unbind() const {
	shader->release();
	va->unbind();
	ib->unbind();
	textures[active_text].unbind();
}

void Sprite::draw() const {
	bind();
	glDrawElements(GL_TRIANGLES, ib->get_count(), GL_UNSIGNED_INT, nullptr);
}

unsigned int Sprite::get_texture_count() const {
	return tex_count;
}

void Sprite::set_active_texture_idx(unsigned int index) {
	active_text = index;
}

unsigned int Sprite::get_active_texture_idx() const {
	return active_text;
}
