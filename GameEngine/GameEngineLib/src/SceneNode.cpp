#include "SceneNode.h"

SceneNode::SceneNode()
{

}

SceneNode::SceneNode(Mesh *newMesh, ShaderProgram *shader, const Matrix4 &model)
{
	mesh = newMesh;
	sh = shader;
	modelMatrix = model;
}

SceneNode::~SceneNode()
{
	delete mesh;
	delete sh;
	for (std::vector<SceneNode*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		delete (*it);
	}
}

void SceneNode::setParent(SceneNode *parentNode)
{
	parent = parentNode;
}

void SceneNode::setShader(ShaderProgram *shader)
{
	sh = shader;
}

void SceneNode::setMesh(Mesh *newMesh)
{
	mesh = newMesh;
}

void SceneNode::setModelMatrix(const Matrix4 &model)
{
	modelMatrix = model;
}

void SceneNode::addChild(SceneNode *child)
{
	child->setParent(this);
	children.push_back(child);
}

void SceneNode::removeChild(SceneNode *child)
{
	for (std::vector<SceneNode*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		if ((*it) == child)
		{
			children.erase(it);
		}
	}
}

void SceneNode::draw(Matrix4 &model, ShaderProgram *shader)
{
	ShaderProgram *useShader = NULL;
	Matrix4 modelTemp = model * modelMatrix;

	if (sh == NULL)
	{
		useShader = shader;
	}
	else
	{
		useShader = sh;
	}

	if (mesh != NULL)
	{
		useShader->useProgram();
		mesh->draw(useShader->getUniform("ModelMatrix"), modelTemp);
		useShader->disableProgram();
	}

	for (std::vector<SceneNode*>::iterator it = children.begin(); it != children.end(); ++it) 
	{
		(*it)->draw(modelTemp, useShader);
	}
}