#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Vector3 dir, Vector3 amb, Vector3 diff, Vector3 spec)
{
	Light(amb, diff, spec);
	direction = dir;
}