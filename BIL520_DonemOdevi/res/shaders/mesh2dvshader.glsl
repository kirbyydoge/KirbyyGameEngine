#version 330 core

layout(location = 0) in vec2 pos;

uniform mat4 u_model_proj;

void main() {
	gl_Position = u_model_proj * vec4(pos.x, pos.y, 0.1f, 1);
};