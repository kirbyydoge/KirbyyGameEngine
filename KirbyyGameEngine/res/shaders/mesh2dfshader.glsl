#version 330 core

layout(location = 0) out vec4 color;
in vec4 v_pos;

void main() {
	color = vec4(1, 1, 1, 0.1);
};