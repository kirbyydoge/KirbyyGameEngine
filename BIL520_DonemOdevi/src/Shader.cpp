#include "Shader.h"

#include <GL/glew.h>
#include "glm/glm.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& path_vs, const std::string& path_fs) {
	std::string vs = read_shader_file(path_vs);
	std::string fs = read_shader_file(path_fs);
	id = create_shader_program(vs, fs);
}

Shader::~Shader() {
	glDeleteShader(id);
}

void Shader::use() const {
	glUseProgram(id);
}

void Shader::release() const {
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

template <typename T>
void Shader::set_uniform(const std::string& name, const T value) {
	static_assert(false);
}

template <>
void Shader::set_uniform<glm::vec4>(const std::string& name, const glm::vec4 value) {
	glUniform4f(get_uniform_location(name), value.x, value.y, value.z, value.w);
}

template <>
void Shader::set_uniform<glm::vec3>(const std::string& name, const glm::vec3 value) {
	glUniform3f(get_uniform_location(name), value.x, value.y, value.z);
}

template <>
void Shader::set_uniform<glm::vec2>(const std::string& name, const glm::vec2 value) {
	glUniform2f(get_uniform_location(name), value.x, value.y);
}

template <>
void Shader::set_uniform<float>(const std::string& name, const float value) {
	glUniform1f(get_uniform_location(name), value);
}

template <>
void Shader::set_uniform<int>(const std::string& name, const int value) {
	glUniform1i(get_uniform_location(name), value);
}

int Shader::get_uniform_location(const std::string& name) {
	auto search = uloc_cache.find(name);
	if (search != uloc_cache.end()) {
		return search->second;
	}
	int loc = glGetUniformLocation(id, name.c_str());
	if (loc == -1) {
		std::cout << "WARN: No such uniform (" << name << ")" << std::endl;
	}
	uloc_cache[name] = loc;
	return loc;
}
