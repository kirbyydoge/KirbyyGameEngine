#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <unordered_map>

class Shader {
public:
	Shader(const std::string& path_vs, const std::string& path_fs);
	~Shader();
	void use() const;
	void release() const;
	template <typename T>
	void set_uniform(const std::string& name, const T value);
	template <typename T>
	void set_uniform_matrix(const std::string& name, const T& value);
private:
	unsigned int id;
	std::unordered_map<std::string, int> uloc_cache;

	int get_uniform_location(const std::string& name);
	unsigned int compile_shader(unsigned int type, const std::string& source);
	unsigned int create_shader_program(const std::string& vertex_shader, const std::string& fragment_shader);
	std::string read_shader_file(const std::string& path);
};