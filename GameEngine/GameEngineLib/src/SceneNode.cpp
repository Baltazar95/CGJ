#include "SceneNode.h"

SceneNode::SceneNode()
{
	MatrixFactory mf;
	worldModel = modelMatrix = mf.identity4();
}

SceneNode::SceneNode(Mesh *newMesh, ShaderProgram *shader, const Matrix4 &model)
{
	MatrixFactory mf;

	mesh = newMesh;
	sh = shader;
	modelMatrix = model;
	worldModel = mf.identity4();
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

Vector3 SceneNode::getWorldPosition()
{
	return Vector3(worldModel.matrix[12], worldModel.matrix[13], worldModel.matrix[14]);
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
	//mesh->update(model);
	for (std::vector<SceneNode*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		(*it)->update(worldModel);
	}
}

void SceneNode::draw(ShaderProgram *shader, const Vector3 &lightPos)
{
	MatrixFactory mf;
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

		if (useShader->containsUniform("LightPos"))
		{

			glUniformMatrix3fv(useShader->getUniform("NormalMatrix"), 1, GL_FALSE, mf.convert4To3(mf.normalMatrix(worldModel)).matrix);
			glUniformMatrix4fv(useShader->getUniform("ModelMatrix"), 1, GL_FALSE, worldModel.matrix);
			const GLfloat pos[] = { lightPos.x, lightPos.y, lightPos.z };
			//glUniform3fv(useShader->getUniform("ViewPosition"), 1, pos);
			glUniform3fv(useShader->getUniform("LightPos"), 1, pos);
			mesh->draw(useShader->getUniform("ModelMatrix"), useShader->getUniform("LightPos"), worldModel, lightPos);
		}
		else
		{
			mesh->draw(useShader->getUniform("ModelMatrix"), worldModel);
		}

		useShader->disableProgram();
	}

	for (std::vector<SceneNode*>::iterator it = children.begin(); it != children.end(); ++it) 
	{
		(*it)->draw(useShader, lightPos);
	}
}