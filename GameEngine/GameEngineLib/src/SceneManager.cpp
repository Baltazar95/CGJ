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
	meshes = std::map<std::string, Mesh*>();

	Matrix4 S, R, T;

	//shader creation
	ShaderProgram *blShader = createBlinnPhongShader();
	ShaderProgram *moonShader = createMoonShader();
	ShaderProgram *textureShader = createSimpleTextureShader();
	waterShader = createWaterShader();


/* */
	//import materials
	MaterialLoader ml;
	ml.loadMaterialData(std::string("../../GameEngine/GameEngineLib/src/Meshes/bridge.mtl"));

	TextureLoader tl;
	//por aqui todas as texturas
	//texture 1 - wood
	tl.loadTextureData(std::string("../../GameEngine/GameEngineLib/src/Textures/wood.jpg"));
	//texture 2
	tl.loadTextureData(std::string("../../GameEngine/GameEngineLib/src/Textures/metal.jpg"));

	Texture *watertex = new Texture("water", NULL);
	//Texture *watertex = new Texture(std::string("../../GameEngine/GameEngineLib/src/Textures/metal.jpg"));
	materials = ml.getMaterials();
	textures = tl.getTextures();

	Obj_Loader loaderCube = Obj_Loader(std::string("../../GameEngine/GameEngineLib/src/Meshes/Cube.obj"), &meshes, "Cube");
	//loader->processMeshData(vertices, normals, texCoords);
	//delete loader;

/* */
	//setup cameras
	camera = new Camera(UBO_BP, Vector3(0.0f, 0.0f, -20.0f));
	camera->setOrthographic(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 50.0f);
	camera->setPerspective(30.0f, (640.0f / 480.0f), 1.0f, 50.0f);

/* */
	//setup scene
	sceneGraph = new SceneNode(nullptr, /*blShader*/textureShader, mf.identity4(), nullptr, nullptr);

/* */
	T = mf.translation(-25.0f, -20.0f, 0.0f);
	S = mf.scale(50.0f, 0.1f, 50.0f, 1.0f);
	water = new SceneNode(meshes["Cube"], nullptr, T*S, nullptr, textures["wood"]);

	sceneGraph->addChild(water);

/* */
	T = mf.translation(-1.0f, -1.0f, 0.0f);
	cube = new SceneNode(meshes["Cube"], nullptr, T, nullptr, textures["wood"]);
	sceneGraph->addChild(cube);

/* * /
	T = mf.translation(-1.0f, -1.0f, 0.0f);
	bridge = new SceneNode(meshes[""], nullptr, T, nullptr, textures["wood"]);
	sceneGraph->addChild(bridge);

/* */
	T = mf.translation(1.5f, 1.5f, 3.0f);
	light = new SceneNode(meshes["Cube"], moonShader, T, materials["lambert4SG"], nullptr);
	sceneGraph->addChild(light);

/* */
	waterShader->useProgram();
	glUniform1i(waterShader->getUniform("screenTexture"), 0);
	waterShader->disableProgram();

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	fbo = new FrameBuffer(watertex->getTexture(), 640, 480);
}

SceneManager::~SceneManager()
{
	delete sceneGraph;
	delete camera;
	sceneGraph = nullptr;
	camera = nullptr;
}

ShaderProgram *SceneManager::createBlinnPhongShader()
{
	ShaderProgram *shader = new ShaderProgram();
	shader->addShader("../../GameEngine/GameEngineLib/src/Shaders/BlinnPhongVertexShader.glsl", GL_VERTEX_SHADER);
	shader->addShader("../../GameEngine/GameEngineLib/src/Shaders/BlinnPhongFragmentShader.glsl", GL_FRAGMENT_SHADER);
	shader->compileShaders();
	shader->createShaderProgram();
	shader->addAttribute(VERTICES, "inPosition");
	shader->addAttribute(TEXCOORDS, "inTexcoord");
	shader->addAttribute(NORMALS, "inNormal");
	shader->linkProgram();

	//material properties
	shader->addUniform("material.ambient");
	shader->addUniform("material.diffuse");
	shader->addUniform("material.specular");
	shader->addUniform("material.shininess");
	shader->addUniform("material.emissive");

	//light properties
	shader->addUniform("light.position");
	shader->addUniform("light.ambient");
	shader->addUniform("light.diffuse");
	shader->addUniform("light.specular");

	shader->addUniform("NormalMatrix");
	shader->addUniform("ModelMatrix");

	//shader->addUniform("tex");

	//shader->addUniform("ViewPosition");
	shader->addUniformBlock("SharedMatrices", UBO_BP);

	return shader;
}

ShaderProgram *SceneManager::createMoonShader()
{
	ShaderProgram *shader = new ShaderProgram();
	shader->addShader("../../GameEngine/GameEngineLib/src/Shaders/MoonVertexShader.glsl", GL_VERTEX_SHADER);
	shader->addShader("../../GameEngine/GameEngineLib/src/Shaders/MoonFragmentShader.glsl", GL_FRAGMENT_SHADER);
	shader->compileShaders();
	shader->createShaderProgram();
	shader->addAttribute(VERTICES, "inPosition");
	shader->linkProgram();
	shader->addUniform("ModelMatrix");
	shader->addUniformBlock("SharedMatrices", UBO_BP);

	return shader;
}

ShaderProgram *SceneManager::createSimpleTextureShader()
{
	ShaderProgram *shader = new ShaderProgram();
	shader->addShader("../../GameEngine/GameEngineLib/src/Shaders/SimpleTextureVertexShader.glsl", GL_VERTEX_SHADER);
	shader->addShader("../../GameEngine/GameEngineLib/src/Shaders/SimpleTextureFragmentShader.glsl", GL_FRAGMENT_SHADER);
	shader->compileShaders();
	shader->createShaderProgram();
	shader->addAttribute(VERTICES, "inPosition");
	shader->addAttribute(TEXCOORDS, "inTexcoord");
	shader->addAttribute(NORMALS, "inNormal");
	shader->linkProgram();

	//material properties
	shader->addUniform("material.ambient");
	shader->addUniform("material.diffuse");
	shader->addUniform("material.specular");
	shader->addUniform("material.shininess");
	shader->addUniform("material.emissive");

	//light properties
	shader->addUniform("light.position");
	shader->addUniform("light.ambient");
	shader->addUniform("light.diffuse");
	shader->addUniform("light.specular");

	shader->addUniform("NormalMatrix");
	shader->addUniform("ModelMatrix");

	shader->addUniform("tex");

	//shader->addUniform("ViewPosition");
	shader->addUniformBlock("SharedMatrices", UBO_BP);

	return shader;
}

ShaderProgram *SceneManager::createWaterShader()
{
	ShaderProgram *shader = new ShaderProgram();
	shader->addShader("../../GameEngine/GameEngineLib/src/Shaders/WaterVertexShader.glsl", GL_VERTEX_SHADER);
	shader->addShader("../../GameEngine/GameEngineLib/src/Shaders/WaterFragmentShader.glsl", GL_FRAGMENT_SHADER);
	shader->compileShaders();
	shader->createShaderProgram();
	shader->addAttribute(VERTICES, "position");
	shader->linkProgram();
	shader->addUniform("ModelMatrix");
	shader->addUniform("screenTexture");

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
	if (frameType == REFLECTION)
	{
		camera->setCamera();

		sceneGraph->draw(nullptr, light->getWorldPosition(), fbo);
		water->setIsIt();
		frameType = BLOOM;
	}
	else if (frameType == BLOOM)
	{
		camera->setCamera();

		sceneGraph->draw(nullptr, light->getWorldPosition(), fbo);
		water->setIsIt();
		frameType = REFLECTION;
	}
	//else if (frameType == NORMAL)
	//{
	//	camera->setCamera();



	//	frameType = REFLECTION;
	////}
	//camera->setCamera();
	//sceneGraph->draw(nullptr, light->getWorldPosition());
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
	glUniform4fv(waterShader->getUniform("ModelMatrix"), 1, mf.rotation(Vector3(1.0f, 0.0f, 0.0f), 45.0f).matrix);
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, fbo->getRenderedTex());	// use the color attachment texture as the texture of the quad plane
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindTexture(GL_TEXTURE_2D, 0);
	waterShader->disableProgram();
}