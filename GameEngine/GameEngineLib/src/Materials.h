#ifndef __MATERIALS_H__
#define __MATERIALS_H__

#include <string>
#include <sstream>
class Materials {

private:
	std::string _mat_name;
	float _ambient[3]; //Ka
	float _diffuse[3]; //Kd
	float _specular[3]; //Ks
	float _emission[3]; //Ke
	float _shininess; //Ns
	float _Ni; //dont know what it is yet
	float _dissolve; //d - 1== opaque; 0 == fully transparent
	int _illum;
	std::string _map_Kd; //path to texture, looks like

public:
	Materials();
	Materials(std::stringstream &sin);
	std::string getName();
	void parseName(std::stringstream &sin);
	void parseAmbient(std::stringstream &sin);
	void parseDiffuse(std::stringstream &sin);
	void parseSpecular(std::stringstream &sin);
	void parseEmission(std::stringstream &sin);
	void parseShininess(std::stringstream &sin);
	void parseNi(std::stringstream &sin);
	void parseDissolve(std::stringstream &sin);
	void parseIllum(std::stringstream &sin);
	void parseMapPath(std::stringstream &sin);


};

#endif // !__MATERIALS_H__
