#include "SceneManager.h"

SceneManager::SceneManager()
{
	Matrix4 S, R, T;
	ShaderProgram *sh = createShader();

	//TODO
	ml.loadMaterialData(std::string("../../GameEngine/GameEngineLib/src/Meshes/bridge.mtl"));

	materials = ml.getMaterials();
	
	camera = new Camera(UBO_BP, Vector3(0.0f, 0.0f, -20.0f));
	camera->setOrthographic(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 50.0f);
	camera->setPerspective(30.0f, (640.0f / 480.0f), 1.0f, 50.0f);


	//TODO
	tangram = new SceneNode(nullptr, sh, mf.identity4(), materials.find("lambert2SG")->second);


	sceneGraph = tangram;
/* * /
	S = mf.scale(10.0f, 10.0f, 0.1f, 1.0f);
	R = mf.rotation(Vector4(0.0f, 1.0f, 0.0f, 0.0f), 180.0f);
	T = mf.translation(10.0f, -10.0f, -1.1f);
	base = new SceneNode(new Mesh("../../GameEngine/GameEngineLib/src/Meshes/Cube.obj"), nullptr, T*R*S);
	sceneGraph->addChild(base);
/* */
	//T = mf.translation(1.0f, -1.0f, 0.0f);
	T = mf.translation(-1.0f, -1.0f, 0.0f);

	//TODO
	cube = new SceneNode(new Mesh("../../GameEngine/GameEngineLib/src/Meshes/Cube.obj"), nullptr, T, materials.find("lambert3SG")->second);

	sceneGraph->addChild(cube);
/* */
	ShaderProgram *shader = new ShaderProgram();
	shader->addShader("../../GameEngine/GameEngineLib/src/Shaders/MoonVertexShader.glsl", GL_VERTEX_SHADER);
	shader->addShader("../../GameEngine/GameEngineLib/src/Shaders/MoonFragmentShader.glsl", GL_FRAGMENT_SHADER);
	shader->compileShaders();
	shader->createShaderProgram();
	shader->addAttribute(VERTICES, "in_Position");
	shader->linkProgram();
	shader->addUniform("ModelMatrix");
	shader->addUniformBlock("SharedMatrices", UBO_BP);
/* */
	T = mf.translation(3.0f, 3.0f, -3.0f);
	light = new SceneNode(new Mesh("../../GameEngine/GameEngineLib/src/Meshes/Cube.obj"), shader, T, materials.find("lambert4SG")->second);
	sceneGraph->addChild(light);
/* * /
	R = mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f), -45.0f);
	T = mf.translation(-1.0f, -3.2f, 0.0f);
	parallelepiped = new SceneNode(new Mesh("../../GameEngine/GameEngineLib/src/Meshes/Parallelepiped.obj"), nullptr, T*R);
	sceneGraph->addChild(parallelepiped);
/* * /
	R = mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f), -90.0f);
	T = mf.translation(3.1f, 1.0f, 0.0f);
	smallPyramideRight = new SceneNode(new Mesh("../../GameEngine/GameEngineLib/src/Meshes/Pyramide.obj"), nullptr, T*R);
	sceneGraph->addChild(smallPyramideRight);
/* * /
	R = mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f), 180.0f);
	T = mf.translation(-1.1f, -1.1f, 0.0f);
	smallPyramideLeft = new SceneNode(new Mesh("../../GameEngine/GameEngineLib/src/Meshes/Pyramide.obj"), nullptr, T*R);
	sceneGraph->addChild(smallPyramideLeft);
/* * /
	S = mf.scale(1.45f, 1.45f, 1.0f, 0.0f);
	R = mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f), 45.0f);
	T = mf.translation(1.0f, -3.1f, 0.0f);
	pyramide = new SceneNode(new Mesh("../../GameEngine/GameEngineLib/src/Meshes/Pyramide.obj"), nullptr, T*R*S);
	sceneGraph->addChild(pyramide);
/* * /
	S = mf.scale(2.0f, 2.0f, 1.0f, 1.0f);
	R = mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f), 0.0f);
	T = mf.translation(-1.0f, 1.1f, 0.0f);
	bigPyramideRight = new SceneNode(new Mesh("../../GameEngine/GameEngineLib/src/Meshes/Pyramide.obj"), nullptr, T*R*S);
	sceneGraph->addChild(bigPyramideRight);
/* * /
	S = mf.scale(2.0f, 2.0f, 1.0f, 1.0f);
	R = mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f), 90.0f);
	T = mf.translation(-1.1f, -1.0f, 0.0f);
	bigPyramideLeft = new SceneNode(new Mesh("../../GameEngine/GameEngineLib/src/Meshes/Pyramide.obj"), nullptr, T*R*S);
	sceneGraph->addChild(bigPyramideLeft);
/* */
}

SceneManager::~SceneManager()
{
	delete sceneGraph;
	delete camera;
	sceneGraph = nullptr;
	camera = nullptr;
}

ShaderProgram *SceneManager::createShader()
{
	ShaderProgram *shader = new ShaderProgram();
	shader->addShader("../../GameEngine/GameEngineLib/src/Shaders/BlinnPhongVertexShader.glsl", GL_VERTEX_SHADER);
	shader->addShader("../../GameEngine/GameEngineLib/src/Shaders/BlinnPhongFragmentShader.glsl", GL_FRAGMENT_SHADER);
	shader->compileShaders();
	shader->createShaderProgram();
	shader->addAttribute(VERTICES, "in_Position");
	shader->addAttribute(TEXCOORDS, "inTexcoord");
	shader->addAttribute(NORMALS, "inNormal");
	shader->linkProgram();
	shader->addUniform("LightPos");
	shader->addUniform("ModelMatrix");
	shader->addUniformBlock("SharedMatrices", UBO_BP);

	return shader;
}

void SceneManager::updateScene(const float &deltaAnglex, const float &deltaAngley, const float &fov, const int &elapsed)
{
	float astep = 0.05f * elapsed;
	float vstep = 0.00025f * elapsed;
	float mSpeed = 0.025f * elapsed;

	camera->updateView(deltaAnglex, deltaAngley, fov, elapsed);

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

	sceneGraph->update(mf.translation(position));
}

void SceneManager::drawScene()
{
	camera->setCamera();
	sceneGraph->draw(nullptr, light->getWorldPosition());
}