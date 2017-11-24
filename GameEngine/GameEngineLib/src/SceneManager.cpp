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

	if ((KeyBuffer::instance()->isPressed('e') || KeyBuffer::instance()->isPressed('E')) && !animationOn)
	{
		switchAnimationMode();
		animationOn = true;
	}

	bool isFinished = false;
	if (animationMode == ON)
	{
		if (!(cubeActual == cubeTranslation))
		{
			isFinished = false;
			if (cubeActual.x - vstep < cubeTranslation.x)
			{
				cubeActual.x = cubeTranslation.x;
			}
			else
			{
				cubeActual.x = cubeActual.x - vstep;
			}
			if (cubeActual.y - vstep < cubeTranslation.y)
			{
				cubeActual.y = cubeTranslation.y;
			}
			else
			{
				cubeActual.y = cubeActual.y - vstep;
			}
			cube->setModelMatrix(mf.translation(cubeActual.x, cubeActual.y, cubeActual.z));
		}
		else
		{
			isFinished = true;
		}

		if (!(parallelepipedActual == parallelepipedTranslation) || (parallelepipedActualRotationZ != parallelepipedRotationZ) || (parallelepipedActualRotationY != parallelepipedRotationY))
		{
			isFinished = false;
			if (parallelepipedActual.x - vstep < parallelepipedTranslation.x)
			{
				parallelepipedActual.x = parallelepipedTranslation.x;
			}
			else
			{
				parallelepipedActual.x = parallelepipedActual.x - vstep;
			}
			if (parallelepipedActual.y + vstep > parallelepipedTranslation.y)
			{
				parallelepipedActual.y = parallelepipedTranslation.y;
			}
			else
			{
				parallelepipedActual.y = parallelepipedActual.y + vstep;
			}

			if (parallelepipedActualRotationY + astep > parallelepipedRotationY)
			{
				parallelepipedActualRotationY = parallelepipedRotationY;
				if (parallelepipedActualRotationZ + astep > parallelepipedRotationZ)
				{
					parallelepipedActualRotationZ = parallelepipedRotationZ;
				}
				else
				{
					parallelepipedActualRotationZ += astep;
				}
			}
			else
			{
				parallelepipedActualRotationY += astep;
			}
			parallelepiped->setModelMatrix(mf.translation(parallelepipedActual.x, parallelepipedActual.y, parallelepipedActual.z) * mf.rotation(Vector4(0.0f, 1.0f, 0.0f, 0.0f), parallelepipedActualRotationY) * mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f),parallelepipedActualRotationZ));
		}

		if (!(pyramideActual == pyramideTranslation))
		{
			isFinished = false;
			if (pyramideActual.x - vstep < pyramideTranslation.x)
			{
				pyramideActual.x = pyramideTranslation.x;
			}
			else
			{
				pyramideActual.x = pyramideActual.x - vstep;
			}
			if (pyramideActual.y - vstep < pyramideTranslation.y)
			{
				pyramideActual.y = pyramideTranslation.y;
			}
			else
			{
				pyramideActual.y = pyramideActual.y - vstep;
			}
			pyramide->setModelMatrix(mf.translation(pyramideActual.x, pyramideActual.y, pyramideActual.z) * mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f), 45.0f) * mf.scale(1.45f, 1.45f, 1.0f, 0.0f));
		}

		if (!(smallLeftActual == smallLeftTranslation))
		{
			isFinished = false;
			if (smallLeftActual.x + vstep > smallLeftTranslation.x)
			{
				smallLeftActual.x = smallLeftTranslation.x;
			}
			else 
			{
				smallLeftActual.x = smallLeftActual.x + vstep;
			}
			if (smallLeftActual.y + vstep > smallLeftTranslation.y)
			{
				smallLeftActual.y = smallLeftTranslation.y;
			}
			else
			{
				smallLeftActual.y = smallLeftActual.y + vstep;
			}
			smallPyramideLeft->setModelMatrix(mf.translation(smallLeftActual.x, smallLeftActual.y, smallLeftActual.z) * mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f), 180.0f));
		}

		if (!(smallRightActual == smallRightTranslation))
		{
			isFinished = false;
			if (smallRightActual.x - vstep < smallRightTranslation.x)
			{
				smallRightActual.x = smallRightTranslation.x;
			}
			else
			{
				smallRightActual.x = smallRightActual.x - vstep;
			}
			if (smallRightActual.y - vstep < smallRightTranslation.y)
			{
				smallRightActual.y = smallRightTranslation.y;
			}
			else
			{
				smallRightActual.y = smallRightActual.y - vstep;
			}
			smallPyramideRight->setModelMatrix(mf.translation(smallRightActual.x, smallRightActual.y, smallRightActual.z) * mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f), -90.0f));
		}

		if (!(bigLeftActual == bigLeftTranslation))
		{
			isFinished = false;
			if (bigLeftActual.x + vstep > bigLeftTranslation.x)
			{
				bigLeftActual.x = bigLeftTranslation.x;
			}
			else
			{
				bigLeftActual.x = bigLeftActual.x + vstep;
			}
			if (bigLeftActual.y + vstep > bigLeftTranslation.y)
			{
				bigLeftActual.y = bigLeftTranslation.y;
			}
			else
			{
				bigLeftActual.y = bigLeftActual.y + vstep;
			}
			bigPyramideLeft->setModelMatrix(mf.translation(bigLeftActual.x, bigLeftActual.y, bigLeftActual.z) * mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f), 90.0f) * mf.scale(2.0f, 2.0f, 1.0f, 1.0f));
 
		}

		if (!(bigRightActual == bigRightTranslation))
		{
			isFinished = false;
			if (bigRightActual.x + vstep > bigRightTranslation.x)
			{
				bigRightActual.x = bigRightTranslation.x;
			}
			else
			{
				bigRightActual.x = bigRightActual.x + vstep;
			}
			if (bigRightActual.y - vstep < bigRightTranslation.y)
			{
				bigRightActual.y = bigRightTranslation.y;
			}
			else
			{
				bigRightActual.y = bigRightActual.y - vstep;
			}
			bigPyramideRight->setModelMatrix(mf.translation(bigRightActual.x, bigRightActual.y, bigRightActual.z) * mf.scale(2.0f, 2.0f, 1.0f, 1.0f));
		}
	}

	else
	{
		if (!(cubeActual == initCubeTranslation))
		{
			isFinished = false;
			if (cubeActual.x + vstep > initCubeTranslation.x)
			{
				cubeActual.x = initCubeTranslation.x;
			}
			else
			{
				cubeActual.x = cubeActual.x + vstep;
			}
			if (cubeActual.y + vstep > initCubeTranslation.y)
			{
				cubeActual.y = initCubeTranslation.y;
			}
			else
			{
				cubeActual.y = cubeActual.y + vstep;
			}
			cube->setModelMatrix(mf.translation(cubeActual.x, cubeActual.y, cubeActual.z));
		}
		else
		{
			isFinished = true;
		}

		if (!(parallelepipedActual == initParallelepipedTranslation) || (parallelepipedActualRotationZ != initParallelepipedRotationZ) || (parallelepipedActualRotationY != initParallelepipedRotationY))
		{
			isFinished = false;
			if (parallelepipedActual.x + vstep > initParallelepipedTranslation.x)
			{
				parallelepipedActual.x = initParallelepipedTranslation.x;
			}
			else
			{
				parallelepipedActual.x = parallelepipedActual.x + vstep;
			}
			if (parallelepipedActual.y - vstep < initParallelepipedTranslation.y)
			{
				parallelepipedActual.y = initParallelepipedTranslation.y;
			}
			else
			{
				parallelepipedActual.y = parallelepipedActual.y - vstep;
			}

			if (parallelepipedActualRotationY - astep < initParallelepipedRotationY)
			{
				parallelepipedActualRotationY = initParallelepipedRotationY;

				if (parallelepipedActualRotationZ - astep < initParallelepipedRotationZ)
				{
					parallelepipedActualRotationZ = initParallelepipedRotationZ;
				}
				else
				{
					parallelepipedActualRotationZ -= astep;
				}
			}
			else
			{
				parallelepipedActualRotationY -= astep;
			}
			parallelepiped->setModelMatrix(mf.translation(parallelepipedActual.x, parallelepipedActual.y, parallelepipedActual.z) * mf.rotation(Vector4(0.0f, 1.0f, 0.0f, 0.0f), parallelepipedActualRotationY) * mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f), parallelepipedActualRotationZ));
		}

		if (!(pyramideActual == initPyramideTranslation))
		{
			isFinished = false;
			if (pyramideActual.x + vstep > initPyramideTranslation.x)
			{
				pyramideActual.x = initPyramideTranslation.x;
			}
			else
			{
				pyramideActual.x = pyramideActual.x + vstep;
			}
			if (pyramideActual.y + vstep > initPyramideTranslation.y)
			{
				pyramideActual.y = initPyramideTranslation.y;
			}
			else
			{
				pyramideActual.y = pyramideActual.y + vstep;
			}
			pyramide->setModelMatrix(mf.translation(pyramideActual.x, pyramideActual.y, pyramideActual.z) * mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f), 45.0f) * mf.scale(1.45f, 1.45f, 1.0f, 0.0f));
		}

		if (!(smallLeftActual == initSmallLeftTranslation))
		{
			isFinished = false;
			if (smallLeftActual.x - vstep < initSmallLeftTranslation.x)
			{
				smallLeftActual.x = initSmallLeftTranslation.x;
			}
			else
			{
				smallLeftActual.x = smallLeftActual.x - vstep;
			}
			if (smallLeftActual.y - vstep < initSmallLeftTranslation.y)
			{
				smallLeftActual.y = initSmallLeftTranslation.y;
			}
			else
			{
				smallLeftActual.y = smallLeftActual.y - vstep;
			}
			smallPyramideLeft->setModelMatrix(mf.translation(smallLeftActual.x, smallLeftActual.y, smallLeftActual.z) * mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f), 180.0f));
		}

		if (!(smallRightActual == initSmallRightTranslation))
		{
			isFinished = false;
			if (smallRightActual.x + vstep > initSmallRightTranslation.x)
			{
				smallRightActual.x = initSmallRightTranslation.x;
			}
			else
			{
				smallRightActual.x = smallRightActual.x + vstep;
			}
			if (smallRightActual.y + vstep > initSmallRightTranslation.y)
			{
				smallRightActual.y = initSmallRightTranslation.y;
			}
			else
			{
				smallRightActual.y = smallRightActual.y + vstep;
			}
			smallPyramideRight->setModelMatrix(mf.translation(smallRightActual.x, smallRightActual.y, smallRightActual.z) * mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f), -90.0f));
		}

		if (!(bigLeftActual == initBigLeftTranslation))
		{
			isFinished = false;
			if (bigLeftActual.x - vstep < initBigLeftTranslation.x)
			{
				bigLeftActual.x = initBigLeftTranslation.x;
			}
			else
			{
				bigLeftActual.x = bigLeftActual.x - vstep;
			}
			if (bigLeftActual.y - vstep < initBigLeftTranslation.y)
			{
				bigLeftActual.y = initBigLeftTranslation.y;
			}
			else
			{
				bigLeftActual.y = bigLeftActual.y - vstep;
			}
			bigPyramideLeft->setModelMatrix(mf.translation(bigLeftActual.x, bigLeftActual.y, bigLeftActual.z) * mf.rotation(Vector4(0.0f, 0.0f, 1.0f, 0.0f), 90.0f) * mf.scale(2.0f, 2.0f, 1.0f, 1.0f));

		}

		if (!(bigRightActual == initBigRightTranslation))
		{
			isFinished = false;
			if (bigRightActual.x - vstep < initBigRightTranslation.x)
			{
				bigRightActual.x = initBigRightTranslation.x;
			}
			else
			{
				bigRightActual.x = bigRightActual.x - vstep;
			}
			if (bigRightActual.y + vstep > initBigRightTranslation.y)
			{
				bigRightActual.y = initBigRightTranslation.y;
			}
			else
			{
				bigRightActual.y = bigRightActual.y + vstep;
			}
			bigPyramideRight->setModelMatrix(mf.translation(bigRightActual.x, bigRightActual.y, bigRightActual.z) * mf.scale(2.0f, 2.0f, 1.0f, 1.0f));
		}
	}
	if (isFinished)
	{
		animationOn = false;
	}


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