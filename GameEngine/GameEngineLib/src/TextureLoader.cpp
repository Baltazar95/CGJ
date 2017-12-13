#include "TextureLoader.h"


void TextureLoader::loadTextureData(std::string &filename) {
	std::ifstream ifile(filename);
	std::string line, str;
	std::stringstream aux;
	Texture *text = new Texture();
	while (std::getline(ifile, line)) {
		std::stringstream aux(line);
		aux >> str;

		if (str.compare("newmtl") == 0) {
			text = new Texture(aux);
			//_textures[text->getName()] = text;
		}

		else {
			parseTexture(text, std::stringstream(line));
		}


	}

}



void TextureLoader::parseTexture(Texture *text, std::stringstream& sin) {
	std::string s;
	sin >> s;

	//if (s.compare("Ns") == 0)
		//tex->parseShininess(sin);

	//else if (s.compare("Ka") == 0)
		//tex->parseAmbient(sin);


}

std::map<std::string, Texture*> TextureLoader::getTextures() {

	return _textures;
}