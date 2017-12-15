#ifndef __TEXTURE_H__
#define __TEXTURE_H__
#include <string>
#include <sstream>
#include "GlUtils.h"
#include "stb_image.h"

class Texture {

private:
	unsigned int texture;
	std::string _texture_name;
	int width, height, nrChannels;
	unsigned char *data;

public:

	Texture() {};
	Texture(std::string &sin);
	Texture(std::string name, char* data);
	unsigned int getTexture() {
		return texture;
	};

	std::string Texture::getName();
	void setTexture(unsigned int tex) { texture = tex; }
};

#endif // !__TEXTURE_H__
