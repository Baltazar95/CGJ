#ifndef __GLUTILS_H__
#define  __GLUTILS_H__

#include "GL/glew.h"
#include "GL/freeglut.h"

#include <iostream>
#include <string>

namespace GlUtils
{
	void checkOpenGLError(std::string error);
	bool isOpenGLError();
}

#endif // !__GLUTILS_H__