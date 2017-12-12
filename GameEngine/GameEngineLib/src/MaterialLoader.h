#ifndef __MATERIALLOADER_H__
#define __MATERIALLOADER_H__

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include "Materials.h"

class MaterialLoader {
	
	private:
		std::map<std::string, Materials> _materials;
		
	public:

		void loadMaterialData(std::string &filename);
		void parseMaterial(Materials &mat, std::stringstream& sin);
		std::map<std::string, Materials> getMaterials();


};

#endif // !__MATERIALLOADER_H__
