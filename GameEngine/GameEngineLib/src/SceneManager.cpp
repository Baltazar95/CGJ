#include "SceneManager.h"

SceneManager::SceneManager()
{
	MatrixFactory mf;
	Matrix4 S, R, T;

	modelMatrix = mf.identity4();

	ShaderProgram *sh = createShader();

	camera = new Camera(UBO_BP, Vector3(0.0f, 0.0f, -20.0f));
	camera->setOrthographic(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 50.0f);
	camera->setPerspective(30.0f, (640.0f / 480.0f), 1.0f, 50.0f);

	tangram = new SceneNode(NULL, sh, modelMatrix);

	sceneGraph = tangram;

	S = mf.scale(10.0f, 10.0f, 0.1f, 1.0f);
	R = mf.rotation(Vector4(0.0f, 1.0f, 0.0f, 0.0f), 180.0f);
	T = mf.translation(10.0f, -10.0f, -1.1f);
	base = new SceneNode(new Mesh("../../GameEngine/GameEngineLib/src/Meshes/Cube.obj"), NULL, T*R*S);
	sceneGraph->addChild(base);

	T = mf.translation(1.0f, -1.0f, 0.0f);
	initCubeTranslation = cubeActual = Vector3(1.0f, -1.0f, 0.0f);
	cube = new SceneNode(new Mesh("../../GameEngine/GameEngineLib/src/Meshes/Cube.obj"), NULL, T);
	sceneGraph->addChild(cube);

	R = mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f), -45.0f);
	parallelepipedActualRotationZ = -45.0f;
	parallelepipedActualRotationY = 0.0f;
	T = mf.translation(-1.0f, -3.2f, 0.0f);
	initParallelepipedTranslation = parallelepipedActual = Vector3(-1.0f, -3.2f, 0.0f);
	parallelepiped = new SceneNode(new Mesh("../../GameEngine/GameEngineLib/src/Meshes/Parallelepiped.obj"), NULL, T*R);
	sceneGraph->addChild(parallelepiped);

	R = mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f), -90.0f);
	T = mf.translation(3.1f, 1.0f, 0.0f);
	initSmallRightTranslation = smallRightActual = Vector3(3.1f, 1.0f, 0.0f);
	smallPyramideRight = new SceneNode(new Mesh("../../GameEngine/GameEngineLib/src/Meshes/Pyramide.obj"), NULL, T*R);
	sceneGraph->addChild(smallPyramideRight);

	R = mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f), 180.0f);
	T = mf.translation(-1.1f, -1.1f, 0.0f);
	initSmallLeftTranslation = smallLeftActual = Vector3(-1.1f, -1.1f, 0.0f);
	smallPyramideLeft = new SceneNode(new Mesh("../../GameEngine/GameEngineLib/src/Meshes/Pyramide.obj"), NULL, T*R);
	sceneGraph->addChild(smallPyramideLeft);

	S = mf.scale(1.45f, 1.45f, 1.0f, 0.0f);
	R = mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f), 45.0f);
	T = mf.translation(1.0f, -3.1f, 0.0f);
	initPyramideTranslation = pyramideActual = Vector3(1.0f, -3.1f, 0.0f);
	pyramide = new SceneNode(new Mesh("../../GameEngine/GameEngineLib/src/Meshes/Pyramide.obj"), NULL, T*R*S);
	sceneGraph->addChild(pyramide);

	S = mf.scale(2.0f, 2.0f, 1.0f, 1.0f);
	R = mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f), 0.0f);
	T = mf.translation(-1.0f, 1.1f, 0.0f);
	initBigRightTranslation = bigRightActual = Vector3(-1.0f, 1.1f, 0.0f);
	bigPyramideRight = new SceneNode(new Mesh("../../GameEngine/GameEngineLib/src/Meshes/Pyramide.obj"), NULL, T*R*S);
	sceneGraph->addChild(bigPyramideRight);

	S = mf.scale(2.0f, 2.0f, 1.0f, 1.0f);
	R = mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f), 90.0f);
	T = mf.translation(-1.1f, -1.0f, 0.0f);
	initBigLeftTranslation = bigLeftActual = Vector3(-1.1f, -1.0f, 0.0f);
	bigPyramideLeft = new SceneNode(new Mesh("../../GameEngine/GameEngineLib/src/Meshes/Pyramide.obj"), NULL, T*R*S);
	sceneGraph->addChild(bigPyramideLeft);
}

SceneManager::~SceneManager()
{
	delete sceneGraph;
	delete camera;
	sceneGraph = NULL;
	camera = NULL;
}

ShaderProgram *SceneManager::createShader()
{
	ShaderProgram *shader = new ShaderProgram();
	shader->addShader("../../GameEngine/GameEngineLib/src/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
	shader->addShader("../../GameEngine/GameEngineLib/src/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
	shader->compileShaders();
	shader->createShaderProgram();
	shader->addAttribute(VERTICES, "in_Position");
	shader->addAttribute(TEXCOORDS, "inTexcoord");
	shader->addAttribute(NORMALS, "inNormal");
	shader->linkProgram();
	shader->addUniform("ModelMatrix");
	shader->addUniformBlock("SharedMatrices", UBO_BP);

	return shader;
}

void SceneManager::updateScene(float deltaAnglex, float deltaAngley, float fov, int elapsed)
{
	float astep = 0.05f * elapsed;
	float vstep = 0.00025f * elapsed;
	float mSpeed = 0.025f * elapsed;
	MatrixFactory mf;

	camera->updateView(deltaAnglex, deltaAngley, fov);

	if (KeyBuffer::instance()->isPressed('w') || KeyBuffer::instance()->isPressed('W'))
	{
		position += camera->getFront() * mSpeed;
	}
	if (KeyBuffer::instance()->isPressed('s') || KeyBuffer::instance()->isPressed('S'))
	{
		position -= camera->getFront() * mSpeed;
	}
	if (KeyBuffer::instance()->isPressed('a') || KeyBuffer::instance()->isPressed('A'))
	{
		position -= normalized(camera->getSide()) * mSpeed;
	}
	if (KeyBuffer::instance()->isPressed('d') || KeyBuffer::instance()->isPressed('D'))
	{
		position += normalized(camera->getSide()) * mSpeed;
	}

	modelMatrix = mf.translation(position);
}

void SceneManager::drawScene()
{
	camera->setCamera();
	sceneGraph->draw(modelMatrix, NULL);
}

void SceneManager::switchAnimationMode()
{
	if (animationMode == OFF)
	{
		animationMode = ON;
	}
	else
	{
		animationMode = OFF;
	}
}