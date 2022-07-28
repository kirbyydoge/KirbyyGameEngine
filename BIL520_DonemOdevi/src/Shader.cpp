#include "Shader.h"

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
