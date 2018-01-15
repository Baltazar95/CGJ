#include "PointLight.h"

PointLight::PointLight(Vector3 pos, float k, float lin, float quad, Vector3 amb, Vector3 diff, Vector3 spec)
{
	Light(amb, diff, spec);
	position = pos;
	constant = k;
	linear = lin;
	quadratic = quad;
}