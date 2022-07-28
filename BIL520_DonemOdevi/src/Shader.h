#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Shader {
	Shader();
	~Shader();
	static unsigned int compile_shader(unsigned int type, const std::string& source);
	static unsigned int create_shader_program(const std::string& vertex_shader, const std::string& fragment_shader);
private:
	unsigned int id;
};