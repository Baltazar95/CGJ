#ifndef __OBJ_LOADER_H__
#define __OBJ_LOADER_H__

#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "MathAux.h"
#include "Mesh.h"

class Obj_Loader
{
	private:
		std::vector <Vector3> vertexData, normalData, vertexInfo, normalInfo, texCoordDataSky;
		std::vector <Vector2> texCoordData, textureInfo;
		std::vector <unsigned int> vertexIdx, texCoordIdx, normalIdx;
		bool texcoordsLoaded = false, normalsLoaded = false;
		std::string meshName;
		bool smoothedFace = true;
		Mesh *createdMesh;
		std::map<std::string, Mesh*> *newMeshes;
		int parts = 0;
		
		void parseVertex(std::stringstream& sin);
		void parseTexcoord(std::stringstream& sin);
		void parseNormal(std::stringstream& sin);
		void parseFace(std::stringstream& sin);
		void parseLine(std::stringstream& sin);
		void parseMesh(std::stringstream& sin);
		void loadMeshData(std::string& filename);

	public:
		Obj_Loader(std::string& filename, std::map<std::string, Mesh*> *meshes, std::string name);
		~Obj_Loader();
		void processMeshData(std::vector<Vector3> &vertices, std::vector<Vector3> &normals, std::vector<Vector2> &texCoords);
};

#endif // !__OBJ_LOADER_H__

