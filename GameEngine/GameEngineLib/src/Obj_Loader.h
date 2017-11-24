#ifndef __OBJ_LOADER_H__
#define __OBJ_LOADER_H__

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "MathAux.h"

class Obj_Loader
{
	private:
		std::vector <Vector3> vertexData, normalData;
		std::vector <Vector2> texCoordData;
		std::vector <unsigned int> vertexIdx, texCoordIdx, normalIdx;
		bool texcoordsLoaded = false, normalsLoaded = false;

		void parseVertex(std::stringstream& sin);
		void parseTexcoord(std::stringstream& sin);
		void parseNormal(std::stringstream& sin);
		void parseFace(std::stringstream& sin);
		void parseLine(std::stringstream& sin);
		void loadMeshData(std::string& filename);

	public:
		Obj_Loader(std::string& filename);
		~Obj_Loader();
		void processMeshData(std::vector<Vector3> &vertices, std::vector<Vector3> &normals, std::vector<Vector2> &texCoords);
};

#endif // !__OBJ_LOADER_H__

