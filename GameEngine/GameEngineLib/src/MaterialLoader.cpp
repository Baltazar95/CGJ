#include "MaterialLoader.h"


void MaterialLoader::loadMaterialData(std::string &filename) {
	std::ifstream ifile(filename);
	std::string line, str;
	std::stringstream aux;
	Material *mat = new Material();
	while (std::getline(ifile, line)) {
		std::stringstream aux(line);
		aux >> str;
		
		if (str.compare("newmtl") == 0) {
			mat = new Material(aux);
			_materials[mat->getName()] = mat;
		}

		else {
			parseMaterial(mat, std::stringstream(line));
		}

		
	}

}



void MaterialLoader::parseMaterial(Material *mat, std::stringstream& sin) {
	std::string s;
	sin >> s;

	if (s.compare("Ns") == 0)
		mat->parseShininess(sin);

	else if (s.compare("Ka") == 0) 
		mat->parseAmbient(sin);

	else if (s.compare("Kd") == 0) 
		mat->parseDiffuse(sin);
	
	else if (s.compare("Ks") == 0) 
		mat->parseSpecular(sin);
	
	else if (s.compare("Ke") == 0) 
		mat->parseEmission(sin);
	
	else if (s.compare("Ni") == 0) 
		mat->parseNi(sin);
	
	else if (s.compare("d") == 0)
		mat->parseDissolve(sin);

	else if (s.compare("illum") == 0) 
		mat->parseIllum(sin);
	
	else if (s.compare("map_Kd") == 0) 
		mat->parseMapPath(sin);

	
}

std::map<std::string, Material*> MaterialLoader::getMaterials() {

	return _materials;
}