#include "OpenGL_API.h"

#define CAPTION "UniBox running"

int WinX = 640, WinY = 480;
int WindowHandle = 0;
unsigned int FrameCount = 0;

float deltaAnglex = 0.0f, deltaAngley = 0.0f, fov = 30.0f;
int xOrigin = -1, yOrigin = -1, elapsed = glutGet(GLUT_ELAPSED_TIME);

SceneManager *sm;

void OpenGL_API::cleanup()
{
	delete sm;
	sm = nullptr;
}

void OpenGL_API::display()
{
	++FrameCount;
	sm->bindFrameBuffer();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//framebuffer
	sm->drawScene();
	sm->unbindFrameBuffer();


	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//default buffer
	sm->drawScene();
	//sm->drawQuad();
	glutSwapBuffers();
}

void OpenGL_API::keysPressed(unsigned char key, int x, int y)
{
	KeyBuffer::instance()->pressKey(key);
}

void OpenGL_API::keysReleased(unsigned char key, int x, int y)
{
	KeyBuffer::instance()->releaseKey(key);
}

void OpenGL_API::mouseButton(int button, int state, int x, int y)
{
	// only start motion if the left button is pressed
	if (button == GLUT_RIGHT_BUTTON) 
	{
		// when the button is released
		if (state == GLUT_UP) 
		{
			xOrigin = -1;
			yOrigin = -1;
		}
		// state = GLUT_DOWN
		else
		{
			xOrigin = x;
			yOrigin = y;
		}
	}
}

void OpenGL_API::mouseMovement(int x, int y)
{
	// this will only be true when the left button is down
	if (xOrigin >= 0) 
	{
		// update deltaAnglex
		deltaAnglex = (xOrigin - x) * 0.2f;
		xOrigin = x;

		// update deltaAngley
		deltaAngley = (yOrigin - y) * 0.2f;
		yOrigin = y;
	}
}

void OpenGL_API::mouseWheel(int button, int direction, int x, int y)
{
	if (direction > 0)
	{
		fov = -5.0f;
	}
	else
	{
		fov = 5.0f;
	}
}

void OpenGL_API::idle()
{
	int difference = glutGet(GLUT_ELAPSED_TIME) - elapsed;
	sm->updateScene(deltaAnglex, deltaAngley, fov, difference);
	deltaAnglex = 0.0f;
	deltaAngley = 0.0f;
	fov = 0.0f;
	elapsed = glutGet(GLUT_ELAPSED_TIME);

	glutPostRedisplay();
}

void OpenGL_API::reshape(int w, int h)
{
	WinX = w;
	WinY = h;
	glViewport(0, 0, WinX, WinY);
}

void OpenGL_API::timer(int value)
{
	std::ostringstream oss;
	oss << CAPTION << ": " << FrameCount << " FPS @ (" << WinX << "x" << WinY << ")";
	std::string s = oss.str();
	glutSetWindow(WindowHandle);
	glutSetWindowTitle(s.c_str());
	FrameCount = 0;
	glutTimerFunc(1000, timer, 0);
}

void OpenGL_API::setupCallbacks()
{
	glutCloseFunc(cleanup);
	glutDisplayFunc(display);

	//Keyboard Functions
	glutKeyboardFunc(keysPressed);
	glutKeyboardUpFunc(keysReleased);

	//Mouse Functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMovement);
	glutMouseWheelFunc(mouseWheel);

	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);

}

void OpenGL_API::checkOpenGLInfo()
{
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cerr << "OpenGL Renderer: " << renderer << " (" << vendor << ")" << std::endl;
	std::cerr << "OpenGL version " << version << std::endl;
	std::cerr << "GLSL version " << glslVersion << std::endl;
}

void OpenGL_API::setupOpenGL()
{
	checkOpenGLInfo();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void OpenGL_API::setupGLEW()
{
	glewExperimental = GL_TRUE;
	GLenum result = glewInit();
	if (result != GLEW_OK) {
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	GLenum err_code = glGetError();
}

void OpenGL_API::setupGLUT(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(3, 3);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(WinX, WinY);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	WindowHandle = glutCreateWindow(CAPTION);
	if (WindowHandle < 1) {
		std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void OpenGL_API::init()
{
	setupGLUT(argc, argv);
	setupGLEW();
	setupOpenGL();
	sm = new SceneManager();
	setupCallbacks();

}

OpenGL_API::OpenGL_API(int _argc, char* _argv[])
{
	argc = _argc;
	argv = _argv;
	init();
}

int OpenGL_API::run()
{
	glutMainLoop();
	exit(EXIT_SUCCESS);
}