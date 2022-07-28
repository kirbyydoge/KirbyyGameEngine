#pragma once
#include "ObjectComponent.h"
#include "glm_extended.h"

class Transform : ObjectComponent {
public:
	Transform();
	Transform(glm::vec3 pos, glm::vec3 scale, glm::vec3 transform);
	~Transform();
	void set_pos(glm::vec3 pos);
	glm::vec3 get_pos();
	void set_scale(glm::vec3 scale);
	glm::vec3 get_scale();
	void set_rotation(glm::vec3 rotation);
	glm::vec3 get_rotation();
private:
	glm::vec3 pos;
	glm::vec3 scale;
	glm::vec3 rotation;
};