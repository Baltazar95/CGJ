#include "Material.h"

Material::Material(Vector3 amb, Vector3 diff, Vector3 spec, Vector3 emi, float shine)
{
	_ambient = amb;
	_diffuse = diff;
	_specular = spec;
	_emission = emi;
	_shininess = shine;
}

Material::Material(std::stringstream &sin) {
	parseName(sin);

	_ambient = Vector3();
	_diffuse = Vector3();
	_specular = Vector3();
	_emission = Vector3();
}


/*****************************************
***************** GETTERS ****************
******************************************/

std::string Material::getName() {

	return _mat_name;
}

Vector3 Material::getAmbient() {
	return _ambient;
}

Vector3 Material::getDiffuse() {
	return _diffuse;
}

Vector3 Material::getSpecular() {
	return _specular;
}

Vector3 Material::getEmission() {
	return _emission;
}

float Material::getShininess() {
	return _shininess;
}

float Material::getNi() {
	return _Ni;
}

float Material::getDissolve() {
	return _dissolve;
}

int Material::getIllum() {
	return _illum;
}





void Material::parseName(std::stringstream &sin) {
	sin.ignore(2, ' ');
	sin >> _mat_name;
}

void Material::parseAmbient(std::stringstream &sin) {

	sin >> _ambient;
}

void Material::parseDiffuse(std::stringstream &sin) {

	sin >> _diffuse;
}

void Material::parseSpecular(std::stringstream &sin) {

	sin >> _specular;
}

void Material::parseEmission(std::stringstream &sin) {

	sin >> _emission;

}

void Material::parseShininess(std::stringstream &sin) {
	sin.ignore(2, ' ');
	sin >> _shininess;

}

void Material::parseDissolve(std::stringstream &sin) {
	sin.ignore(2, ' ');
	sin >> _dissolve;
	if (_dissolve == NULL) {
		_dissolve = 1;
	}
}

void Material::parseNi(std::stringstream &sin) {
	sin.ignore(2, ' ');
	sin >> _Ni;
}

void Material::parseIllum(std::stringstream &sin) {
	sin.ignore(2, ' ');
	sin >> _illum;
}

//TODO
void Material::parseMapPath(std::stringstream &sin) {
	sin.ignore(1, ' ');
	sin >> _map_Kd;
}
