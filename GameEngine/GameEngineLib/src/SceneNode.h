#ifndef __SCENENODE_H__
#define __SCENENODE_H__

#include "ShaderProgram.h"
#include "Mesh.h"
#include "MathAux.h"

class SceneNode
{
	private:
		SceneNode *parent;
		std::vector<SceneNode*> children;
		ShaderProgram *sh;
		Mesh *mesh;
		Matrix4 modelMatrix;

	public:
		SceneNode();
		SceneNode(Mesh *newMesh, ShaderProgram *shader, const Matrix4 &model);
		~SceneNode();
		void setParent(SceneNode *parentNode);
		void setShader(ShaderProgram *shader);
		void setMesh(Mesh *mesh);
		void setModelMatrix(const Matrix4 &model);
		void addChild(SceneNode *child);
		void removeChild(SceneNode *child);
		void draw(Matrix4 &model, ShaderProgram *shader);
};

#endif // !__SCENENODE_H__

