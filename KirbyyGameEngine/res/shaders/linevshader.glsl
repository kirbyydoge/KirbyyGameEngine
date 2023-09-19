#version 330 core

layout(location = 0) in vec4 pos;

uniform mat4 u_model_proj;

void main() {
	gl_Position = u_model_proj * pos;
};