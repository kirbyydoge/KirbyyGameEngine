#include "Box2D.h"

Box2D::Box2D(Transform* center, float width, float height) {
	this->center = center;
	dims.x = width;
	dims.y = height;
}

Box2D::~Box2D() {}

bool Box2D::is_inside(glm::vec2 p) {
	std::pair<glm::vec2, glm::vec2> bounds = this->get_bounds();
	return !(
		p.x < bounds.first.x	||
		p.x > bounds.second.x	||
		p.y > bounds.first.y	||
		p.y < bounds.second.y
	);
}

glm::vec2 Box2D::get_dimensions() {
	return dims;
}

std::pair<glm::vec2, glm::vec2> Box2D::get_bounds() {
	// TODO: std::make_pair does not work, convert to struct.
	glm::vec3 center_pos = center->get_pos();
	glm::vec2 llc(center_pos.x - dims.x / 2, center_pos.y - dims.y / 2);
	glm::vec2 urc(center_pos.x + dims.x / 2, center_pos.y + dims.y / 2);
	std::pair<glm::vec2, glm::vec2> bounds;
	bounds.first = llc;
	bounds.second = urc;
	return bounds;
}