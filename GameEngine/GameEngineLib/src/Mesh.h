#ifndef __MESH_H__
#define __MESH_H__

#include <vector>

#include "GlUtils.h"

#include "MathAux.h"
#include "Obj_Loader.h"

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

	public:
		Mesh() {};
		Mesh(std::string filename);
		~Mesh();
		void createBufferObjects();
		void destroyBufferObjects();
		void draw();
};

#endif // !__MESH_H__