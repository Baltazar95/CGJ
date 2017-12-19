#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include <vector>
#include "SceneNode.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Camera.h"
#include "KeyBuffer.h"
#include "FrameBuffer.h"
#include "MaterialLoader.h"
#include "TextureLoader.h"
#include "Obj_Loader.h"

//// FRAME TYPE //////
enum FrameType
{
	REFLECTION,
	BLOOM,
	NORMAL
};
//////////////////////////

class SceneManager
{
	private:
		SceneNode *sceneGraph;
		Camera *camera;
		const GLuint UBO_BP = 0;
		Vector3 position = Vector3(0.0f, 0.0f, 0.0f);
		SceneNode *cube, *light, *water, *bridge, *sky;
		FrameBuffer *fbo;
		ShaderProgram *waterShader;
		unsigned int quadVAO, quadVBO;
		std::map<std::string, Material*> materials;
		FrameType frameType = REFLECTION;
		std::map<std::string, Texture*> textures;
		std::map<std::string, Mesh*> meshes;
	public:
		SceneManager();
		~SceneManager();
		ShaderProgram *createBlinnPhongShader();
		ShaderProgram *createMoonShader();
		ShaderProgram *createSimpleTextureShader();
		ShaderProgram *createWaterShader();
		//TODO missing parameters to update
		void updateScene(const float &deltaAnglex, const float &deltaAngley, const float &fov, const int &elapsed);
		void drawScene();
		void bindFrameBuffer();
		void unbindFrameBuffer();
		void drawQuad();
};


#endif // !__SCENEMANAGER_H__