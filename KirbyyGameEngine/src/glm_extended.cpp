#include "glm_extended.h"

glm::vec2 glm_ext::new_vec2(float x, float y) {
	glm::vec2 vec;
	vec.x = x;
	vec.y = y;
	return vec;
}
glm::vec3 glm_ext::new_vec3(float x, float y, float z) {
	glm::vec3 vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return vec;
}
glm::vec4 glm_ext::new_vec4(float x, float y, float z, float w) {
	glm::vec4 vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	vec.w = w;
	return vec;
}