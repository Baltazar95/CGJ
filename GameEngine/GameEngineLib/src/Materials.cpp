#include "Materials.h"


Materials::Materials(std::stringstream &sin) {
	parseName(sin);

	_ambient = Vector3();
	_diffuse = Vector3();
	_specular = Vector3();
	_emission = Vector3();
}


/*****************************************
***************** GETTERS ****************
******************************************/

std::string Materials::getName() {

	return _mat_name;
}

Vector3 Materials::getAmbient() {
	return _ambient;
}

Vector3 Materials::getDiffuse() {
	return _diffuse;
}

Vector3 Materials::getSpecular() {
	return _specular;
}

Vector3 Materials::getEmission() {
	return _emission;
}

float Materials::getShininess() {
	return _shininess;
}

float Materials::getNi() {
	return _Ni;
}

float Materials::getDissolve() {
	return _dissolve;
}

int Materials::getIllum() {
	return _illum;
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
	if (_dissolve == NULL) {
		_dissolve = 1;
	}
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
