#include "SceneNode.h"

SceneNode::SceneNode()
{
	MatrixFactory mf;
	worldModel = modelMatrix = mf.identity4();
}

SceneNode::SceneNode(Mesh *newMesh, ShaderProgram *shader, const Matrix4 &model, Material *m, Texture *newTexture)
{
	MatrixFactory mf;

	mesh = newMesh;
	sh = shader;
	modelMatrix = model;
	texture = newTexture;
	material = m;
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

void SceneNode::setTexture(unsigned int tex) {
	texture->setTexture(tex);
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
			break;
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

void SceneNode::draw(ShaderProgram *shader, const Vector3 &lightPos, const Vector3 &cameraPosition, FrameBuffer *fbo)
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

		if (material != nullptr)
		{
			const GLfloat ambient[] = { material->getAmbient().x, material->getAmbient().y, material->getAmbient().z };
			glUniform3fv(useShader->getUniform("material.ambient"), 1, ambient);

			const GLfloat diffuse[] = { material->getDiffuse().x, material->getDiffuse().y, material->getDiffuse().z };
			glUniform3fv(useShader->getUniform("material.diffuse"), 1, diffuse);

			const GLfloat specular[] = { material->getSpecular().x, material->getSpecular().y, material->getSpecular().z };
			glUniform3fv(useShader->getUniform("material.specular"), 1, specular);

			const GLfloat emissive[] = { material->getSpecular().x, material->getSpecular().y, material->getSpecular().z };
			glUniform3fv(useShader->getUniform("material.emissive"), 1, emissive);

			glUniform1f(useShader->getUniform("material.shininess"), material->getShininess());
		}

		const GLfloat pos[] = { lightPos.x, lightPos.y, lightPos.z };
		glUniform3fv(useShader->getUniform("light.position"), 1, pos);

		const GLfloat lambient[] = { 0.2f, 0.2f, 0.2f };
		glUniform3fv(useShader->getUniform("light.ambient"), 1, lambient);

		const GLfloat ldiffuse[] = { 0.5f, 0.5f, 0.5f };
		glUniform3fv(useShader->getUniform("light.diffuse"), 1, ldiffuse);

		const GLfloat lspecular[] = { 1.0f, 1.0f, 1.0f };
		glUniform3fv(useShader->getUniform("light.specular"), 1, lspecular);

		glUniformMatrix4fv(useShader->getUniform("NormalMatrix"), 1, GL_FALSE, mf.normalMatrix(modelMatrix).matrix);
		glUniformMatrix4fv(useShader->getUniform("ModelMatrix"), 1, GL_FALSE, modelMatrix.matrix);

		const GLfloat camPos[] = { cameraPosition.x, cameraPosition.y, cameraPosition.z };
		glUniform3fv(useShader->getUniform("ViewPosition"), 1, camPos);

		// bind Texture
		if (texture != nullptr && !((texture->getName()).compare("sky") == 0))
		{
			glUniform1i(useShader->getUniform("tex"), 0);
			glBindTexture(GL_TEXTURE_2D, texture->getTexture());
		}

		if (texture != nullptr && (texture->getName()).compare("sky") == 0) {

			glUniform1i(useShader->getUniform("cube_texture"), 0);
			glDepthMask(GL_FALSE);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, texture->getTexture());
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);

			mesh->draw();

			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glDepthMask(GL_TRUE);

			
		}
		else {
			mesh->draw();
		}
		
		useShader->disableProgram();
	}

	for (std::vector<SceneNode*>::iterator it = children.begin(); it != children.end(); ++it) 
	{
		(*it)->draw(useShader, lightPos, cameraPosition, fbo);
	}
}