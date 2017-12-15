#ifndef __MATERIALLOADER_H__
#define __MATERIALLOADER_H__

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include "Material.h"

class MaterialLoader {
	
	private:
		std::map<std::string, Material*> _materials;
	
	public:

		void loadMaterialData(std::string &filename);
		void parseMaterial(Material *mat, std::stringstream& sin);
		std::map<std::string, Material*> getMaterials();


};

#endif // !__MATERIALLOADER_H__
