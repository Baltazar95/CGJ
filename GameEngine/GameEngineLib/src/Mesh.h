#ifndef __MESH_H__
#define __MESH_H__

#include <vector>

#include "GlUtils.h"

#include "MathAux.h"

#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2

class Mesh
{

	private:
		GLuint VaoId, vboVertices, vboTexCoords, vboNormals;
		std::vector<Vector3> vertices;
		std::vector<Vector3> normals;
		std::vector<Vector2> texCoords;
		std::string material_n;
		std::string texture_n;

	public:
		Mesh() {};
		Mesh(std::vector<Vector3> &newvertices, std::vector<Vector3> &newnormals, std::vector<Vector2> &newtexCoords);
		~Mesh();
		void createBufferObjects();
		void destroyBufferObjects();
		void draw();
};

#endif // !__MESH_H__