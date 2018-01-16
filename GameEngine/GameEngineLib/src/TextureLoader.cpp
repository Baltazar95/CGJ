#include "TextureLoader.h"


void TextureLoader::loadTextureData(std::string &filename) {

	Texture *text = new Texture(filename);

	_textures[text->getName()] = text;

}


void TextureLoader::loadCubeMapData(std::string &front, std::string &back, std::string &up, std::string &down, std::string &left, std::string &right) {

	Texture *text = new Texture(filename);

	_textures[text->getName()] = text;

}

unsigned int TextureLoader::addNullTexture(std::string &filename) {

	Texture *text = new Texture(filename, NULL);

	_textures[text->getName()] = text;

	return text->getTexture();
}

std::map<std::string, Texture*> TextureLoader::getTextures() {

	return _textures;
}