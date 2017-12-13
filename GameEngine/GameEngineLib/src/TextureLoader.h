#ifndef __TEXTURELOADER_H__
#define __TEXTURELOADER_H__

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include "Texture.h"
#include "stb_image.h"

class TextureLoader {

private:
	std::map<std::string, Texture*> _textures;

public:

	void loadTextureData(std::string &filename);
	void parseTexture(Texture *tex, std::stringstream& sin);
	std::map<std::string, Texture*> getTextures();


};

#endif // !__TEXTURELOADER_H__
