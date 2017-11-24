#ifndef __OPENGL_ABSTRACT_API_H__
#define __OPENGL_ABSTRACT_API_H__

#include "GlUtils.h"

class OpenGL_Abstract_API
{
	protected:
		int argc;
		char** argv;

	private:
		virtual void init() = 0;

	public:
		virtual int run() = 0;
};

#endif // !__OPENGL_ABSTRACT_API_H__