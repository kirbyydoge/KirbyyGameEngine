#pragma once
#include "Bounds2D.h"
#include "Transform.h"
#include <utility>

class Box2D : public Bounds2D {
public:
	Box2D(Transform* center, float width, float height);
	~Box2D();
	virtual bool is_inside(glm::vec2 point);
	glm::vec2 get_dimensions();
	std::pair<glm::vec2, glm::vec2> get_bounds();
private:
	Transform* center;
	glm::vec2 dims;
};