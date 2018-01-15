#ifndef __POINTLIGHT_H__
#define __POINTLIGHT_H__

#include "Light.h"

class PointLight : Light
{
	private:
		Vector3 position;
		float constant;
		float linear;
		float quadratic;

	public:
		PointLight() {};
		PointLight(Vector3 pos, float k, float lin, float quad, Vector3 amb, Vector3 diff, Vector3 spec);
		~PointLight() {};
		Vector3 getPosition() { return position; };
		float getConstant() { return constant; };
		float getLinear() { return linear; };
		float getQuadratic() { return quadratic; };
};

#endif // !__POINTLIGHT_H__

