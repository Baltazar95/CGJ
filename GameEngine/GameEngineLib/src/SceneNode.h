#ifndef __SCENENODE_H__
#define __SCENENODE_H__

#include "ShaderProgram.h"
#include "Mesh.h"
#include "MathAux.h"
#include "Texture.h"
#include "Materials.h"
#include "FrameBuffer.h"

class SceneNode
{
	private:
		SceneNode *parent;
		std::vector<SceneNode*> children;
		ShaderProgram *sh;
		Mesh *mesh;
		Materials *material;
		Matrix4 modelMatrix, worldModel;
		Texture *texture;
		bool isIt = false;

	public:
		SceneNode();
		SceneNode(Mesh *newMesh, ShaderProgram *shader, const Matrix4 &model, Materials *m, Texture *newTexture);
		~SceneNode();
		void setParent(SceneNode *parentNode);
		void setShader(ShaderProgram *shader);
		void setMesh(Mesh *mesh);
		void setModelMatrix(const Matrix4 &model);
		void setTexture(unsigned int tex);
		Vector3 getWorldPosition();
		void addChild(SceneNode *child);
		void removeChild(SceneNode *child);
		void update(const Matrix4 &model);
		void draw(ShaderProgram *shader, const Vector3 &lightPos, FrameBuffer *fbo);
		void setIsIt() {
			if (isIt)
				isIt = false;
			else isIt = true;
		};
};

#endif // !__SCENENODE_H__

