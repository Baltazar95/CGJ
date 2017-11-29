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
	mesh = nullptr;
	sh = nullptr;
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

void SceneNode::update(const Matrix4 &model)
{

	worldModel =  model * modelMatrix;
	for (std::vector<SceneNode*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		(*it)->update(worldModel);
	}

}

void SceneNode::draw(ShaderProgram *shader)
{
	ShaderProgram *useShader = nullptr;

	if (sh == nullptr)
	{
		useShader = shader;
	}
	else
	{
		useShader = sh;
	}

	if (mesh != nullptr)
	{
		useShader->useProgram();
		mesh->draw(useShader->getUniform("ModelMatrix"), worldModel);
		useShader->disableProgram();
	}

	for (std::vector<SceneNode*>::iterator it = children.begin(); it != children.end(); ++it) 
	{
		(*it)->draw(useShader);
	}
}