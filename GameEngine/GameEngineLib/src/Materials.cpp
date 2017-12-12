#include "Materials.h"


Materials::Materials(std::stringstream &sin) {
	parseName(sin);
}


std::string Materials::getName() {

	return _mat_name;
}


void Materials::parseName(std::stringstream &sin) {
	sin.ignore(2, ' ');
	sin >> _mat_name;
}

void Materials::parseAmbient(std::stringstream &sin) {
	
	sin.ignore(1, ' ');
	sin >> _ambient[0];
	sin.ignore(1, ' ');
	sin >> _ambient[1];
	sin.ignore(1, ' ');
	sin >> _ambient[2];

}

void Materials::parseDiffuse(std::stringstream &sin) {
	sin.ignore(1, ' ');
	sin >> _diffuse[0];
	sin.ignore(1, ' ');
	sin >> _diffuse[1];
	sin.ignore(1, ' ');
	sin >> _diffuse[2];

}

void Materials::parseSpecular(std::stringstream &sin) {
	sin.ignore(1, ' ');
	sin >> _specular[0];
	sin.ignore(1, ' ');
	sin >> _specular[1];
	sin.ignore(1, ' ');
	sin >> _specular[2];

}

void Materials::parseEmission(std::stringstream &sin) {
	sin.ignore(1, ' ');
	sin >> _emission[0];
	sin.ignore(1, ' ');
	sin >> _emission[1];
	sin.ignore(1, ' ');
	sin >> _emission[2];

}

void Materials::parseShininess(std::stringstream &sin) {
	sin.ignore(1, ' ');
	sin >> _shininess;

}

void Materials::parseDissolve(std::stringstream &sin) {
	sin.ignore(1, ' ');
	sin >> _dissolve;

}

void Materials::parseNi(std::stringstream &sin) {
	sin.ignore(1, ' ');
	sin >> _Ni;

}

void Materials::parseIllum(std::stringstream &sin) {
	sin.ignore(1, ' ');
	sin >> _illum;

}

void Materials::parseMapPath(std::stringstream &sin) {
	sin.ignore(1, ' ');
	sin >> _map_Kd;

}