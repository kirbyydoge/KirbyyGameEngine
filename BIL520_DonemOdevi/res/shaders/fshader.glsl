#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_tex_coord;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main() {
	color = texture(u_texture, v_tex_coord);
	// color = u_color;
};