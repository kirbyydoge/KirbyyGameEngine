#include "Shader.h"

#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& path_vs, const std::string& path_fs) {
	std::string vs = Shader::read_shader_file(path_vs);
	std::string fs = Shader::read_shader_file(path_fs);
	id = Shader::create_shader_program(vs, fs);
}

Shader::~Shader() {}

void Shader::use() {
	glUseProgram(id);
}

void Shader::release() {
	glUseProgram(0);
}

unsigned int Shader::compile_shader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	int res;
	glGetShaderiv(id, GL_COMPILE_STATUS, &res);
	if (!res) {
		int msg_len;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &msg_len);
		char* msg = (char*)_malloca(msg_len * sizeof(char));
		glGetShaderInfoLog(id, msg_len, &msg_len, msg);
		std::cout << "ERR: Compiling shader failed (" << type << "):" << std::endl;
		std::cout << msg << std::endl;
		glDeleteShader(id);
		_freea(msg);
		return 0;
	}
	return id;
}

unsigned int Shader::create_shader_program(const std::string& vertex_shader, const std::string& fragment_shader) {
	unsigned int id = glCreateProgram();
	unsigned int vs = Shader::compile_shader(GL_VERTEX_SHADER, vertex_shader);
	unsigned int fs = Shader::compile_shader(GL_FRAGMENT_SHADER, fragment_shader);
	glAttachShader(id, vs);
	glAttachShader(id, fs);
	glLinkProgram(id);
	glValidateProgram(id);
	glDeleteShader(vs);
	glDeleteShader(fs);
	return id;
}

std::string Shader::read_shader_file(const std::string& path) {
	auto program = std::ostringstream();
	std::ifstream program_file(path);
	if (!program_file.is_open()) {
		std::cout << "ERR: Could not open shader program file: " << path << std::endl;
		return std::string("");
	}
	program << program_file.rdbuf();
	return program.str();
}
