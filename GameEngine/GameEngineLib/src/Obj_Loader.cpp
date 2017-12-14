#include "Obj_Loader.h"

Obj_Loader::Obj_Loader(std::string& filename)
{
	vertexData = std::vector<Vector3>();
	normalData = std::vector<Vector3>();
	texCoordData = std::vector<Vector2>();
	vertexIdx = std::vector<unsigned int>();
	normalIdx = std::vector<unsigned int>();
	texCoordIdx = std::vector<unsigned int>();

	loadMeshData(filename);
}

Obj_Loader::~Obj_Loader()
{
	vertexData.clear();
	texCoordData.clear();
	normalData.clear();
	vertexIdx.clear();
	texCoordIdx.clear();
	normalIdx.clear();
}

void Obj_Loader::processMeshData(std::vector<Vector3> &vertices, std::vector<Vector3> &normals, std::vector<Vector2> &texCoords)
{
	for (unsigned int i = 0; i < vertexIdx.size(); i++) {
		unsigned int vi = vertexIdx[i];
		Vector3 v = vertexData[vi - 1];
		vertices.push_back(v);
		if (texcoordsLoaded) {
			unsigned int ti = texCoordIdx[i];
			Vector2 t = texCoordData[ti - 1];
			texCoords.push_back(t);
		}
		if (normalsLoaded) {
			unsigned int ni = normalIdx[i];
			Vector3 n = normalData[ni - 1];
			normals.push_back(n);
		}
	}
}

void Obj_Loader::parseVertex(std::stringstream& sin)
{
	Vector3 v;
	sin >> v;
	vertexData.push_back(v);
}

void Obj_Loader::parseTexcoord(std::stringstream& sin)
{
	Vector2 t;
	sin >> t;
	texCoordData.push_back(t);
}

void Obj_Loader::parseNormal(std::stringstream& sin)
{
	Vector3 n;
	sin >> n;
	normalData.push_back(n);
}

void Obj_Loader::parseFace(std::stringstream& sin)
{
	std::string token;
	for (int i = 0; i < 3; i++) {
		std::getline(sin, token, '/');
		if (token.size() > 0) vertexIdx.push_back(std::stoi(token));
		std::getline(sin, token, '/');
		if (token.size() > 0) texCoordIdx.push_back(std::stoi(token));
		std::getline(sin, token, ' ');
		if (token.size() > 0) normalIdx.push_back(std::stoi(token));
	}
}

void Obj_Loader::parseMesh(std::stringstream& sin)
{


	std::string token;
	token = sin.str();
	std::string last_element(token.substr(token.rfind(" ") + 1));
	if (last_element.size() > 0) material = last_element;

	//NEW MESH


}

void Obj_Loader::parseLine(std::stringstream& sin)
{
	std::string s;
	sin >> s;
	if (s.compare("v") == 0) parseVertex(sin);
	else if (s.compare("vt") == 0) parseTexcoord(sin);
	else if (s.compare("vn") == 0) parseNormal(sin);
	else if (s.compare("usemtl") == 0) parseMesh(sin);
	else if (s.compare("s") == 0) {
		sin >> s;
		if (s.compare("off")) smoothedFace = false;
		else smoothedFace = true;
	}
	else if (s.compare("f") == 0 && !smoothedFace) parseFace(sin);
}

void Obj_Loader::loadMeshData(std::string& filename)
{
	std::ifstream ifile(filename);
	std::string line;
	while (std::getline(ifile, line)) {
		parseLine(std::stringstream(line));
	}
	texcoordsLoaded = (texCoordIdx.size() > 0);
	normalsLoaded = (normalIdx.size() > 0);
	//processMeshData(vertexAux, normalAux, texCoordAux);
}