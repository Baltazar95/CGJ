#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include <vector>
#include "SceneNode.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Camera.h"
#include "KeyBuffer.h"

//// ANIMATION MODE //////
enum AnimationMode
{
	ON,
	OFF
};

class SceneManager
{
	private:
		SceneNode *sceneGraph;
		Camera *camera;
		const GLuint UBO_BP = 0;
		Matrix4 modelMatrix;
		Vector3 position = Vector3(0.0f, 0.0f, 0.0f);
		SceneNode *tangram, *base, *cube, *pyramide, *smallPyramideLeft, *smallPyramideRight, *bigPyramideLeft, *bigPyramideRight, *parallelepiped;
		AnimationMode animationMode = OFF;
		Vector3 cubeTranslation = Vector3(0.05f, -2.05f, 0.0f), cubeActual = Vector3(), initCubeTranslation = Vector3();
		Vector3 parallelepipedTranslation = Vector3(-2.1f, -2.1f, 0.0f), parallelepipedActual = Vector3(), initParallelepipedTranslation = Vector3();
		float parallelepipedRotationZ = 45.0f, initParallelepipedRotationZ = -45.0f, parallelepipedRotationY = 180.0f, initParallelepipedRotationY = 0.0f, parallelepipedActualRotationZ = 0.0f, parallelepipedActualRotationY = 0.0f;
		Vector3 pyramideTranslation = Vector3(0.05f, -4.2f, 0.0f), pyramideActual = Vector3(), initPyramideTranslation = Vector3();
		Vector3 smallLeftTranslation = Vector3(-0.05f, -0.05f, 0.0f), smallLeftActual = Vector3(), initSmallLeftTranslation = Vector3();
		Vector3 smallRightTranslation = Vector3(2.1f, -0.05f, 0.0f), smallRightActual = Vector3(), initSmallRightTranslation = Vector3();
		Vector3 bigLeftTranslation = Vector3(-0.05f, 0.05f, 0.0f), bigLeftActual = Vector3(), initBigLeftTranslation = Vector3();
		Vector3 bigRightTranslation = Vector3(0.05f, 0.05f, 0.0f), bigRightActual = Vector3(), initBigRightTranslation = Vector3();
		bool animationOn = false;

	public:
		SceneManager();
		~SceneManager();
		ShaderProgram *createShader();
		//TODO missing parameters to update
		void updateScene(float deltaAnglex, float deltaAngley, float fov, int elapsed);
		void drawScene();
		void switchAnimationMode();
};

#endif // !__SCENEMANAGER_H__