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

	sin >> _ambient;
}

void Materials::parseDiffuse(std::stringstream &sin) {

	sin >> _diffuse;
}

void Materials::parseSpecular(std::stringstream &sin) {

	sin >> _specular;
}

void Materials::parseEmission(std::stringstream &sin) {

	sin >> _emission;

}

void Materials::parseShininess(std::stringstream &sin) {
	sin.ignore(2, ' ');
	sin >> _shininess;

}

void Materials::parseDissolve(std::stringstream &sin) {
	sin.ignore(2, ' ');
	sin >> _dissolve;
}

void Materials::parseNi(std::stringstream &sin) {
	sin.ignore(2, ' ');
	sin >> _Ni;
}

void Materials::parseIllum(std::stringstream &sin) {
	sin.ignore(2, ' ');
	sin >> _illum;
}

//TODO
void Materials::parseMapPath(std::stringstream &sin) {
	sin.ignore(1, ' ');
	sin >> _map_Kd;
}
