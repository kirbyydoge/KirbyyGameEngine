#version 330 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec2 tex_coord;

out vec2 v_tex_coord;

void main() {
	gl_Position = pos;
	v_tex_coord = tex_coord;
};