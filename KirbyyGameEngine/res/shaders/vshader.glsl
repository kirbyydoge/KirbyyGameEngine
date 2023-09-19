#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex_coord;

out vec2 v_tex_coord;

uniform mat4 u_model_proj;
uniform mat4 u_model_view;

void main() {
	gl_Position = u_model_proj * u_model_view * vec4(pos.x, pos.y, 0.9f, 1);
	v_tex_coord = tex_coord;
};