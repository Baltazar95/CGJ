#ifndef __TEXTURELOADER_H__
#define __TEXTURELOADER_H__

#include <vector>
#include <string>
#include <map>
#include "Texture.h"

class TextureLoader {

private:
	std::map<std::string, Texture*> _textures;

public:

	void loadTextureData(std::string &filename);
	unsigned int addNullTexture(std::string &filename);
	std::map<std::string, Texture*> getTextures();

};

#endif // !__TEXTURELOADER_H__
