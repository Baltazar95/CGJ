#ifndef __ABSTRACT_API_H__
#define __ABSTRACT_API_H__

#include "GlUtils.h"

class Abstract_API
{
	protected:
		int argc;
		char** argv;

	private:
		virtual void init() = 0;

	public:
		virtual int run() = 0;
};

#endif // !__ABSTRACT_API_H__