#include "MaterialLoader.h"


void MaterialLoader::loadMaterialData(std::string &filename) {
	std::ifstream ifile(filename);
	std::string line;
	std::stringstream aux;
	Materials mat;
	while (std::getline(ifile, line)) {
		if (line.compare("#") == 1) {
			if (line.compare("newmtl") == 0) {
				std::stringstream aux(line);
				mat = Materials(aux);
				_materials[mat.getName()] = mat;

			}
			else {
				parseMaterial(mat, std::stringstream(line));
			}

		}
	}

}



void MaterialLoader::parseMaterial(Materials &mat, std::stringstream& sin) {
	std::string s;
	sin >> s;

	if (s.compare("Ns") == 0)
		mat.parseShininess(sin);

	else if (s.compare("Ka") == 0) 
		mat.parseAmbient(sin);

	else if (s.compare("Kd") == 0) 
		mat.parseDiffuse(sin);
	
	else if (s.compare("Ks") == 0) 
		mat.parseSpecular(sin);
	
	else if (s.compare("Ke") == 0) 
		mat.parseEmission(sin);
	
	else if (s.compare("Ni") == 0) 
		mat.parseNi(sin);
	
	else if (s.compare("d") == 0)
		mat.parseDissolve(sin);

	else if (s.compare("illum") == 0) 
		mat.parseIllum(sin);
	
	else if (s.compare("map_Kd") == 0) 
		mat.parseMapPath(sin);
	
	else if (s.compare("#") == 1) 
		mat.parseName(sin);
	
}

std::map<std::string, Materials> MaterialLoader::getMaterials() {

	return _materials;
}