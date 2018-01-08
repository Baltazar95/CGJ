#ifndef __OPENGL_API__
#define __OPENGL_API__

#include "Abstract_API.h"
#include "SceneManager.h"

class OpenGL_API : Abstract_API
{
	private:
		void init();

		////////////////////////// SETUPS ///////////////////////////////
		void setupGLUT(int argc, char* argv[]);
		void setupGLEW();
		void setupOpenGL();
		void checkOpenGLInfo();
		void setupCallbacks();

		//////////////////////// CALLBACKS //////////////////////////////
		static void cleanup();
		static void display();
		static void keysPressed(unsigned char key, int x, int y);
		static void keysReleased(unsigned char key, int x, int y);
		static void mouseButton(int button, int state, int x, int y);
		static void mouseMovement(int x, int y);
		static void mouseWheel(int button, int direction, int x, int y);
		static void idle();
		static void reshape(int w, int h);
		static void timer(int value);

	public:
		OpenGL_API(int argc, char* argv[]);
		int run();
};

#endif // !__OPENGL_API__