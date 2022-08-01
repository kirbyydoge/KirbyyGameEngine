#pragma once
#include "glm/glm.hpp"

class Bounds2D {
public:
	Bounds2D() {}
	virtual bool is_inside(glm::vec2 p) { return false; }
};