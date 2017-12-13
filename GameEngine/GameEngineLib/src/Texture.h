#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>
#include <sstream>
#include "MathAux.h"

class Texture {

private:
	std::string _texture_name;

public:

	Texture() {};
	Texture(std::stringstream &sin);

};

#endif // !__TEXTURE_H__
