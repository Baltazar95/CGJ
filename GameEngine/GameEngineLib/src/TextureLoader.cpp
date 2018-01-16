#include "TextureLoader.h"


void TextureLoader::loadTextureData(std::string &filename) {

	Texture *text = new Texture(filename);

	_textures[text->getName()] = text;

}

void TextureLoader::loadCubeMapData(std::string &filename, std::string &filename, std::string &filename, std::string &filename, std::string &filename, std::string &filename) {

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