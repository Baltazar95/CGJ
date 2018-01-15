#include "Light.h"

Light::Light( Vector3 amb, Vector3 dif, Vector3 spec)
{
	ambient = amb;
	diffuse = dif;
	specular = spec;
}