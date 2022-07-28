#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Shader {
public:
	Shader(const std::string& path_vs, const std::string& path_fs);
	~Shader();
	void use();
	void release();
	static unsigned int compile_shader(unsigned int type, const std::string& source);
	static unsigned int create_shader_program(const std::string& vertex_shader, const std::string& fragment_shader);
	static std::string read_shader_file(const std::string& path);
	unsigned int id;	// TEMPORARILY PUBLIC. SWITCH TO PRIVATE ON PROD.
private:
};