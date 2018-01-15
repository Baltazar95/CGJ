#ifndef __DIRECTONALLIGHT_H__
#define __DIRECTONALLIGHT_H__

#include "Light.h"

class DirectionalLight : Light
{
	private:
		Vector3 direction;

	public:
		DirectionalLight() {};
		DirectionalLight(Vector3 dir, Vector3 amb, Vector3 diff, Vector3 spec);
		~DirectionalLight() {};
		Vector3 getDirection() { return direction; };
};

#endif // !__DIRECTONALLIGHT_H__

