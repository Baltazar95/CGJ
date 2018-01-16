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
	const char* front = "";
	const char* back = "";
	const char* top = "";
	const char* bottom = "";
	const char* left = "";
	const char* right = "";
	GLuint* tex_cube;

public:

	Texture() {};
	Texture(std::string &sin);
	Texture(std::string name, char* data);
	unsigned int getTexture() {
		return texture;
	};

	std::string Texture::getName();
	void setTexture(unsigned int tex) { texture = tex; }
	bool load_cube_map_side(GLuint texture, GLenum side_target, const char* file_name);
	void create_cube_map(const char* front, const char* back, const char* top, const char* bottom, const char* left, const char* right, GLuint* tex_cube);


};

#endif // !__TEXTURE_H__
