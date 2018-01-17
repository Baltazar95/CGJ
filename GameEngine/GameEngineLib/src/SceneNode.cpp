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
		const GLfloat dpos[] = { 0.2f, 1.0f, 0.3f };
		glUniform3fv(useShader->getUniform("dirLight.direction"), 1, dpos);

		const GLfloat dlambient[] = { 0.05f, 0.05f, 0.05f };
		glUniform3fv(useShader->getUniform("dirLight.ambient"), 1, dlambient);

		const GLfloat dldiffuse[] = { 0.4f, 0.4f, 0.4f };
		glUniform3fv(useShader->getUniform("dirLight.diffuse"), 1, dldiffuse);

		const GLfloat dlspecular[] = { 0.5f, 0.5f, 0.5f };
		glUniform3fv(useShader->getUniform("dirLight.specular"), 1, dlspecular);
		

		const GLfloat pos[] = { lightPos.x, lightPos.y, lightPos.z };
		glUniform3fv(useShader->getUniform("pointLights[0].position"), 1, pos);

		const GLfloat lambient[] = { 0.05f, 0.05f, 0.05f };
		glUniform3fv(useShader->getUniform("pointLights[0].ambient"), 1, lambient);

		const GLfloat ldiffuse[] = { 0.8f, 0.8f, 0.8f };
		glUniform3fv(useShader->getUniform("pointLights[0].diffuse"), 1, ldiffuse);

		const GLfloat lspecular[] = { 1.0f, 1.0f, 1.0f };
		glUniform3fv(useShader->getUniform("pointLights[0].specular"), 1, lspecular);

		const GLfloat lconstant = 1.0f;
		glUniform1f(useShader->getUniform("pointLights[0].constant"), lconstant);

		const GLfloat llinear = 0.09f;
		glUniform1f(useShader->getUniform("pointLights[0].linear"), llinear);

		const GLfloat lquadratic = 0.032f;
		glUniform1f(useShader->getUniform("pointLights[0].quadratic"), lquadratic);


		const GLfloat pos1[] = { 1.0f, 0.0f, 0.0f };
		glUniform3fv(useShader->getUniform("pointLights[1].position"), 1, pos1);

		const GLfloat lambient1[] = { 0.05f, 0.05f, 0.05f };
		glUniform3fv(useShader->getUniform("pointLights[1].ambient"), 1, lambient1);

		const GLfloat ldiffuse1[] = { 0.8f, 0.8f, 0.8f };
		glUniform3fv(useShader->getUniform("pointLights[1].diffuse"), 1, ldiffuse1);

		const GLfloat lspecular1[] = { 1.0f, 1.0f, 1.0f };
		glUniform3fv(useShader->getUniform("pointLights[1].specular"), 1, lspecular1);

		const GLfloat lconstant1 = 1.0f;
		glUniform1f(useShader->getUniform("pointLights[1].constant"), lconstant1);

		const GLfloat llinear1 = 0.09f;
		glUniform1f(useShader->getUniform("pointLights[1].linear"), llinear1);

		const GLfloat lquadratic1 = 0.032f;
		glUniform1f(useShader->getUniform("pointLights[1].quadratic"), lquadratic1);


		const GLfloat pos2[] = { 0.0f, 0.0f, -1.0f };
		glUniform3fv(useShader->getUniform("pointLights[2].position"), 1, pos2);

		const GLfloat lambient2[] = { 0.05f, 0.05f, 0.05f };
		glUniform3fv(useShader->getUniform("pointLights[2].ambient"), 1, lambient2);

		const GLfloat ldiffuse2[] = { 0.8f, 0.8f, 0.8f };
		glUniform3fv(useShader->getUniform("pointLights[2].diffuse"), 1, ldiffuse2);

		const GLfloat lspecular2[] = { 1.0f, 1.0f, 1.0f };
		glUniform3fv(useShader->getUniform("pointLights[2].specular"), 1, lspecular2);

		const GLfloat lconstant2 = 1.0f;
		glUniform1f(useShader->getUniform("pointLights[2].constant"), lconstant2);

		const GLfloat llinear2 = 0.09f;
		glUniform1f(useShader->getUniform("pointLights[2].linear"), llinear2);

		const GLfloat lquadratic2 = 0.032f;
		glUniform1f(useShader->getUniform("pointLights[2].quadratic"), lquadratic2);


		const GLfloat pos3[] = { 0.0f, 4.0f, 0.0f };
		glUniform3fv(useShader->getUniform("pointLights[3].position"), 1, pos3);

		const GLfloat lambient3[] = { 0.05f, 0.05f, 0.05f };
		glUniform3fv(useShader->getUniform("pointLights[3].ambient"), 1, lambient3);

		const GLfloat ldiffuse3[] = { 0.8f, 0.8f, 0.8f };
		glUniform3fv(useShader->getUniform("pointLights[3].diffuse"), 1, ldiffuse3);

		const GLfloat lspecular3[] = { 1.0f, 1.0f, 1.0f };
		glUniform3fv(useShader->getUniform("pointLights[3].specular"), 1, lspecular3);

		const GLfloat lconstant3 = 1.0f;
		glUniform1f(useShader->getUniform("pointLights[3].constant"), lconstant3);

		const GLfloat llinear3 = 0.09f;
		glUniform1f(useShader->getUniform("pointLights[3].linear"), llinear3);

		const GLfloat lquadratic3 = 0.032f;
		glUniform1f(useShader->getUniform("pointLights[3].quadratic"), lquadratic3);


		glUniformMatrix4fv(useShader->getUniform("NormalMatrix"), 1, GL_FALSE, mf.normalMatrix(modelMatrix).matrix);
		glUniformMatrix4fv(useShader->getUniform("ModelMatrix"), 1, GL_FALSE, modelMatrix.matrix);

		const GLfloat camPos[] = { cameraPosition.x, cameraPosition.y, cameraPosition.z };
		glUniform3fv(useShader->getUniform("ViewPosition"), 1, camPos);

		// bind Texture
		if (texture != nullptr)
		{
			glUniform1i(useShader->getUniform("tex"), 0);
			glBindTexture(GL_TEXTURE_2D, texture->getTexture());
		}

		if (texture != nullptr && (texture->getName()).compare("sky") == 0) {
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			mesh->draw();
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
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