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
	std::string front, back, top, bottom, left, right;
	GLuint tex_cube;

public:

	Texture() {};
	Texture(std::string &sin);
	Texture(std::string name, char* data);
	Texture(std::string frontfile, std::string backfile, std::string topfile, std::string bottomfile, std::string leftfile, std::string rightfile);

	unsigned int getTexture() {
		return texture;
	};

	std::string Texture::getName();
	void setTexture(unsigned int tex) { texture = tex; }
	bool load_cube_map_side(GLuint tex_cube, GLenum side_target, std::string file_name);


};

#endif // !__TEXTURE_H__
