#include "TextureLoader.h"


void TextureLoader::loadTextureData(std::string &filename) {

	Texture *text = new Texture(filename);

	_textures[text->getName()] = text;


}


std::map<std::string, Texture*> TextureLoader::getTextures() {

	return _textures;
}