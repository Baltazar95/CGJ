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
	std::string getName();

};

#endif // !__TEXTURE_H__
