#include "Transform.h"

Transform::Transform(glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation) {
	this->pos = pos;
	this->scale = scale;
	this->rotation = rotation;
}

Transform::Transform() {
	glm::vec3 zero_vec = glm_ext::new_vec3(0.f, 0.f, 0.f);
	this->pos = zero_vec;
	this->scale = zero_vec;
	this->rotation = zero_vec;
}

Transform::~Transform() {}

void Transform::set_pos(glm::vec3 pos) {
	this->pos = pos;
}

glm::vec3 Transform::get_pos() {
	return pos;
}

void Transform::set_scale(glm::vec3 scale) {
	this->scale = scale;
}

glm::vec3 Transform::get_scale() {
	return scale;
}

void Transform::set_rotation(glm::vec3 rotation) {
	this->rotation = rotation;
}

glm::vec3 Transform::get_rotation() {
	return rotation;
}

