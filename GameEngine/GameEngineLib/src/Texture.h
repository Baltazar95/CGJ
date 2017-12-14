#ifndef __TEXTURE_H__
#define __TEXTURE_H__
#include <string>
#include <sstream>
#include "GlUtils.h"

//#define STB_IMAGE_IMPLEMENTATION
//#define STBI_ASSERT(x)
#include "stb_image.h"

//#define STBI_MALLOC, STBI_REALLOC, and STBI_FREE

class Texture {

private:
	unsigned int texture;
	std::string _texture_name;
	int width, height, nrChannels;

public:

	Texture() {};
	Texture(std::string &sin);
	std::string getName();

};

#endif // !__TEXTURE_H__
