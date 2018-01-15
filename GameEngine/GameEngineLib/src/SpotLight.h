#ifndef __SPOTLIGHT_H__
#define __SPOTLIGHT_H__

#include "Light.h"

class SpotLight : Light
{
	private:
		Vector3 position;
		Vector3 direction;
		float cutOff;

	public:
		SpotLight() {};
		SpotLight(Vector3 pos, Vector3 dir, float cut, Vector3 amb, Vector3 diff, Vector3 spec);
		~SpotLight() {};
		Vector3 getPosition() { return position; };
		Vector3 getDirection() { return direction; };
		float getCutOff() { return cutOff; };
};

#endif // !__SPOTLIGHT_H__

