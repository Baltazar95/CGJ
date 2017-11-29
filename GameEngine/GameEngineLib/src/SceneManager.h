#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include <vector>
#include "SceneNode.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Camera.h"
#include "KeyBuffer.h"

class SceneManager
{
	private:
		SceneNode *sceneGraph;
		Camera *camera;
		const GLuint UBO_BP = 0;
		Vector3 position = Vector3(0.0f, 0.0f, 0.0f);
		SceneNode *tangram, *base, *cube, *pyramide, *smallPyramideLeft, *smallPyramideRight, *bigPyramideLeft, *bigPyramideRight, *parallelepiped;

	public:
		SceneManager();
		~SceneManager();
		ShaderProgram *createShader();
		//TODO missing parameters to update
		void updateScene(const float &deltaAnglex, const float &deltaAngley, const float &fov, const int &elapsed);
		void drawScene();
};

#endif // !__SCENEMANAGER_H__