#pragma once
#include <string>

class Texture {
public:
	Texture();
	Texture(const std::string& path);
	~Texture();
	void bind(unsigned int slot = 0) const;
	void unbind() const;
	void change_tex(const std::string& path);
private:
	unsigned int id;
	unsigned char* buffer;
	int width;
	int height;
	int bpp;
};