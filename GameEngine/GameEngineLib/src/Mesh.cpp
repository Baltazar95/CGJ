#include "Mesh.h"
Mesh::Mesh()
{
	vertices = std::vector<Vector3>();
	normals = std::vector<Vector3>();
	texCoords = std::vector<Vector2>();
}

Mesh::Mesh(std::vector<Vector3> &newvertices, std::vector<Vector3> &newnormals, std::vector<Vector2> &newtexCoords)
{
	vertices = newvertices;
	normals = newnormals;
	texCoords = newtexCoords;

	//Obj_Loader *loader = new Obj_Loader(filename);
	//loader->processMeshData(vertices, normals, texCoords);
	//delete loader;
	createBufferObjects();
}

Mesh::~Mesh()
{
	//TODO: correct error
	//vertices.clear();
	//normals.clear();
	//texCoords.clear();
	destroyBufferObjects();
}

void Mesh::createBufferObjects()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	{
		glGenBuffers(1, &vboVertices);
		glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3), &vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(VERTICES);
		glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);


		if (!texCoords.empty())
		{

			glGenBuffers(1, &vboTexCoords);

			glBindBuffer(GL_ARRAY_BUFFER, vboTexCoords);
			glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(Vector2), &texCoords[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(TEXCOORDS);
			glVertexAttribPointer(TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), 0);
		}

		if (!normals.empty())
		{
			glGenBuffers(1, &vboNormals);

			glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
			glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(Vector3), &normals[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(NORMALS);
			glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);
		}
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GlUtils::checkOpenGLError("ERROR: Could not create VAOs and VBOs");
}

void Mesh::destroyBufferObjects()
{
	glBindVertexArray(VaoId);
	glDisableVertexAttribArray(VERTICES);
	glDeleteBuffers(1, &vboVertices);
	glDeleteBuffers(1, &vboNormals);
	glDeleteBuffers(1, &vboTexCoords);
	glDeleteVertexArrays(1, &VaoId);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	GlUtils::checkOpenGLError("ERROR: Could not delete VAOs and VBOs");
}

void Mesh::draw()
{

	glBindVertexArray(VaoId);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.size());
	glBindVertexArray(0);

	//TODO: well this function blocks the framebuffer, why?
	//GlUtils::checkOpenGLError("ERROR: Could not draw mesh");
}
