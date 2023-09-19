#include "Collider2D.h"
#include "Box2D.h"

Collider2D::Collider2D(Collider2DType type, Bounds2D* bounds, bool is_trigger, bool is_static) {
	this->type = type;
	this->bounds = bounds;
	this->is_trigger = is_trigger;
	this->is_static = is_static;
}

Collider2D::~Collider2D() {}

Collider2DType Collider2D::get_type() {
	return type;
}

void Collider2D::set_trigger(bool is_trigger) {
	this->is_trigger = is_trigger;
}

bool Collider2D::get_trigger() {
	return is_trigger;
}

bool Collider2D::get_static() {
	return is_static;
}

Bounds2D* Collider2D::get_bounds() {
	return bounds;
}

bool Collider2D::is_colliding(Collider2D* other) {
	if (this->type == Collider2DType::BoxCollider2D && other->get_type() == Collider2DType::BoxCollider2D) {
		return collision2D_box_box(this, other);
	}
}

void Collider2D::on_collision(Collider2D* other) {}

bool Collider2D::collision2D_box_box(Collider2D* obj0, Collider2D* obj1) {
	Box2D* bounds0 = dynamic_cast<Box2D*>(obj0->bounds);
	Box2D* bounds1 = dynamic_cast<Box2D*>(obj1->bounds);
	std::pair<glm::vec2, glm::vec2> corners0 = bounds0->get_bounds();
	std::pair<glm::vec2, glm::vec2> corners1 = bounds1->get_bounds();
	glm::vec2 llc0 = corners0.first;
	glm::vec2 llc1 = corners1.first;
	glm::vec2 urc0 = corners0.second;
	glm::vec2 urc1 = corners1.second;
	return (
		llc0.x < urc1.x	&&
		urc0.x > llc1.x	&&
		llc0.y < urc1.y	&&
		urc0.y > llc1.y
	);
}
