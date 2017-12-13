#ifndef __MATERIALS_H__
#define __MATERIALS_H__

#include <string>
#include <sstream>
#include "MathAux.h"
class Materials {

private:
	std::string _mat_name;
	Vector3 _ambient; //Ka
	Vector3 _diffuse; //Kd
	Vector3 _specular; //Ks
	Vector3 _emission; //Ke
	float _shininess; //Ns
	float _Ni; //dont know what it is yet
	float _dissolve; //d - 1== opaque; 0 == fully transparent
	int _illum;
	std::string _map_Kd; //path to texture, looks like

public:
	Materials(){}
	Materials(std::stringstream &sin);
	std::string getName();
	Vector3 getAmbient();
	Vector3 getDiffuse();
	Vector3 getSpecular();
	Vector3 getEmission();
	float getShininess();
	float getNi();
	float getDissolve();
	int getIllum();
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
