#ifndef __SHADERPROGRAM_H__
#define __SHADERPROGRAM_H__

#include "GlUtils.h"

#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <string>

class ShaderProgram
{
	private:
		//usar mapas para guardar uniforms e shaders
		std::map<std::string, GLuint> shaders;
		std::map<std::string, GLint> uniforms;
		GLuint programId;

	public:
		ShaderProgram() { shaders = std::map<std::string, GLuint>();
						uniforms = std::map<std::string, GLint>(); };
		~ShaderProgram();
		void addShader(std::string filename, const GLenum &shaderType);
		void compileShaders();
		void createShaderProgram();
		void addAttribute(int index, const char* attribute);
		void linkProgram();
		void addUniform(const char* attribute);
		void addUniformBlock(const char* attribute, const GLuint &UBO_BP);
		GLint getUniform(const char* attribute);
		void useProgram();
		void disableProgram();
		std::string readFile(const std::string &filename, std::string shaderType);

		void checkCompilationErrors(GLuint shaderId, std::string shaderType);
		void checkProgramLinkageErrors(GLuint progId);

};
#endif // !__SHADERPROGRAM_H__