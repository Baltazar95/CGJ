#include "SpotLight.h"

SpotLight::SpotLight(Vector3 pos, Vector3 dir, float cut, Vector3 amb, Vector3 diff, Vector3 spec)
{
	Light(amb, diff, spec);
	position = pos;
	direction = dir;
	cutOff = cut;
}