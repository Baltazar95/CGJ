#include "Light.h"

Light::Light()
{

}

Light::Light(Vector3 pos, Vector3 amb, Vector3 dif, Vector3 spec)
{
	position = pos;
	ambient = amb;
	diffuse = dif;
	specular = spec;
}

Light::~Light()
{

}