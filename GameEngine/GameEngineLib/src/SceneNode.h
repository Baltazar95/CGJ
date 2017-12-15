#ifndef __SCENENODE_H__
#define __SCENENODE_H__

#include "ShaderProgram.h"
#include "Mesh.h"
#include "MathAux.h"
#include "Texture.h"
#include "Material.h"

class SceneNode
{
	private:
		SceneNode *parent;
		std::vector<SceneNode*> children;
		ShaderProgram *sh;
		Mesh *mesh;
		Material *material;
		Matrix4 modelMatrix, worldModel;
		Texture *texture;

	public:
		SceneNode();
		SceneNode(Mesh *newMesh, ShaderProgram *shader, const Matrix4 &model, Material *m, Texture *newTexture);
		~SceneNode();
		void setParent(SceneNode *parentNode);
		void setShader(ShaderProgram *shader);
		void setMesh(Mesh *mesh);
		void setModelMatrix(const Matrix4 &model);
		Vector3 getWorldPosition();
		void addChild(SceneNode *child);
		void removeChild(SceneNode *child);
		void update(const Matrix4 &model);
		void draw(ShaderProgram *shader, const Vector3 &lightPos);
};

#endif // !__SCENENODE_H__

