#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "MathAux.h" 

class Light
{
	private:
		Vector3 position;
		Vector3 ambient;
		Vector3 diffuse;
		Vector3 specular;

	public:
		Light();
		Light(Vector3 pos, Vector3 amb, Vector3 dif, Vector3 spec);
		~Light();
		Vector3 getPosition() { return position; };
		Vector3 getAmbient() { return ambient; };
		Vector3 getDiffuse() { return diffuse; };
		Vector3 getSpecular() { return specular; };
};

#endif // !__LIGHT_H__

