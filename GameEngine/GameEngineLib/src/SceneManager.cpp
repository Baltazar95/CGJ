#include "SceneManager.h"

SceneManager::SceneManager()
{
	meshes = std::map<std::string, Mesh*>();

	MatrixFactory mf;
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
	//texture SKY
	tl.loadTextureData(std::string("../../GameEngine/GameEngineLib/src/Textures/sky.jpg"));
	//textures = tl.getTextures();

	Texture *watertex = new Texture("water", NULL);
	//Texture *watertex = new Texture(std::string("../../GameEngine/GameEngineLib/src/Textures/metal.jpg"));
	materials = ml.getMaterials();
	textures = tl.getTextures();
	
	Obj_Loader loader = Obj_Loader(std::string("../../GameEngine/GameEngineLib/src/Meshes/Moon.obj"), &meshes, "Moon");
	loader = Obj_Loader(std::string("../../GameEngine/GameEngineLib/src/Meshes/Cube.obj"), &meshes, "Cube");
	loader = Obj_Loader(std::string("../../GameEngine/GameEngineLib/src/Meshes/Bridge.obj"), &meshes, "Bridge");
	loader = Obj_Loader(std::string("../../GameEngine/GameEngineLib/src/Meshes/plane.obj"), &meshes, "Plane");

/* */
	//setup cameras
	camera = new Camera(UBO_BP, Vector3(0.0f, 0.0f, -20.0f));
	camera->setOrthographic(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 50.0f);
	camera->setPerspective(30.0f, (640.0f / 480.0f), 1.0f, 100.0f);

/* */
	//setup scene
	sceneGraph = new SceneNode(nullptr, /*blShader*/textureShader, mf.identity4(), nullptr, nullptr);

/* */
	T = mf.translation(-15.0f, -10.0f, -15.0f);
	S = mf.scale(30.0f, 0.1f, 30.0f, 1.0f);
	water = new SceneNode(meshes["Plane"], nullptr, T*S, materials["lambert6SG"], nullptr);

	sceneGraph->addChild(water);
/* * /
	T = mf.translation(-1.0f, -1.0f, 0.0f);
	cube = new SceneNode(meshes["Cube"], nullptr, T, materials["lambert4SG"], textures["wood"]);
	sceneGraph->addChild(cube);

/* */


	T = mf.translation(-15.0f, -15.0f, -15.0f);
	S = mf.scale(30.0f, 30.0f, 30.0f, 1.0f);
	sky = new SceneNode(meshes["Cube"], nullptr, T*S, materials["lambert2SG"], textures["sky"]);

	sceneGraph->addChild(sky);

/* */

	T = mf.translation(15.0f, -10.0f, -15.0f);
	for (auto member : meshes)
	{
		if (member.first.find("Bridge") != std::string::npos)
		{
			sceneGraph->addChild(new SceneNode(meshes[member.first], nullptr, T, materials[member.second->getMaterialName()], textures["metal"]));
		}
	}

/* */
	T = mf.translation(1.5f, 5.0f, 3.0f);
	light = new SceneNode(meshes["Moon"], moonShader, T, materials["lambert4SG"], nullptr);
	sceneGraph->addChild(light);

/* */
	waterShader->useProgram();
	glUniform1i(waterShader->getUniform("screenTexture"), 0);
	waterShader->disableProgram();

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
	MatrixFactory mf;

	float astep = 0.05f * elapsed;
	float vstep = 0.00025f * elapsed;
	float mSpeed = 0.025f * elapsed;

	camera->updateView(deltaAnglex, deltaAngley, fov, elapsed);

	//if (KeyBuffer::instance()->isPressed('w') || KeyBuffer::instance()->isPressed('W'))
	//{
	//	position += camera->getFront() * mSpeed;
	//}
	//if (KeyBuffer::instance()->isPressed('s') || KeyBuffer::instance()->isPressed('S'))
	//{
	//	position -= camera->getFront() * mSpeed;
	//}
	//if (KeyBuffer::instance()->isPressed('a') || KeyBuffer::instance()->isPressed('A'))
	//{
	//	position -= normalized(camera->getSide()) * mSpeed;
	//}
	//if (KeyBuffer::instance()->isPressed('d') || KeyBuffer::instance()->isPressed('D'))
	//{
	//	position += normalized(camera->getSide()) * mSpeed;
	//}

	sceneGraph->update(mf.translation(position));
}

void SceneManager::drawScene()
{
	if (frameType == REFLECTION)
	{
		sceneGraph->removeChild(water);
		camera->setInvertedCamera();

		sceneGraph->draw(nullptr, light->getWorldPosition(), fbo);
		water->setIsIt();
		frameType = BLOOM;
		sceneGraph->addChild(water);


		//textureShader->useProgram();
		
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_FRONT);

		//camera->specialSetCamera();
		//sky->draw(nullptr, light->getWorldPosition(), fbo);

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		//textureShader->disableProgram();
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