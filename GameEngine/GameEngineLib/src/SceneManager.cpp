#include "SceneManager.h"

float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
						 // positions   // texCoords
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 0.0f,
	1.0f,  1.0f,  1.0f, 1.0f
};

SceneManager::SceneManager()
{
	Matrix4 S, R, T;
	ShaderProgram *sh = createShader();

	camera = new Camera(UBO_BP, Vector3(0.0f, 0.0f, -20.0f));
	camera->setOrthographic(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 50.0f);
	camera->setPerspective(30.0f, (640.0f / 480.0f), 1.0f, 50.0f);

	tangram = new SceneNode(nullptr, sh, mf.identity4());

	sceneGraph = tangram;
/* * /
	S = mf.scale(10.0f, 10.0f, 0.1f, 1.0f);
	R = mf.rotation(Vector4(0.0f, 1.0f, 0.0f, 0.0f), 180.0f);
	T = mf.translation(10.0f, -10.0f, -1.1f);
	base = new SceneNode(new Mesh("../../GameEngine/GameEngineLib/src/Meshes/Cube.obj"), nullptr, T*R*S);
	sceneGraph->addChild(base);
/* */
	//T = mf.translation(1.0f, -1.0f, 0.0f);

	T = mf.translation(-25.0f, -20.0f, 0.0f);
	S = mf.scale(50.0f, 0.1f, 50.0f, 1.0f);
	water = new SceneNode(new Mesh("../../GameEngine/GameEngineLib/src/Meshes/Cube.obj"), nullptr, T*S);
	sceneGraph->addChild(water);

	T = mf.translation(-1.0f, -1.0f, 0.0f);
	cube = new SceneNode(new Mesh("../../GameEngine/GameEngineLib/src/Meshes/Cube.obj"), nullptr, T);
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
	T = mf.translation(2.0f, 1.0f, 3.0f);
	light = new SceneNode(new Mesh("../../GameEngine/GameEngineLib/src/Meshes/Cube.obj"), shader, T);
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

	waterShader = new ShaderProgram();
	waterShader->addShader("../../GameEngine/GameEngineLib/src/Shaders/WaterVertexShader.glsl", GL_VERTEX_SHADER);
	waterShader->addShader("../../GameEngine/GameEngineLib/src/Shaders/WaterFragmentShader.glsl", GL_FRAGMENT_SHADER);
	waterShader->compileShaders();
	waterShader->createShaderProgram();
	waterShader->addAttribute(VERTICES, "position");
	waterShader->linkProgram();
	waterShader->addUniform("screenTexture");

	waterShader->useProgram();
	glUniform1i(waterShader->getUniform("screenTexture"), 0);

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	fbo = new FrameBuffer(640, 480);
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
	shader->addUniform("NormalMatrix");
	shader->addUniform("ModelMatrix");
	shader->addUniform("LightPos");
	//shader->addUniform("ViewPosition");
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

void SceneManager::bindFrameBuffer() {
	fbo->bindFrameBuffer();
}

void SceneManager::unbindFrameBuffer() {
	fbo->unbindFrameBuffer();
}

void SceneManager::drawQuad()
{
	waterShader->useProgram();
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, fbo->getFrame());	// use the color attachment texture as the texture of the quad plane
	glDrawArrays(GL_TRIANGLES, 0, 6);
}