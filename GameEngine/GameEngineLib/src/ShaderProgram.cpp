#include "ShaderProgram.h"

ShaderProgram::~ShaderProgram()
{
	shaders.clear();
	uniforms.clear();

	glUseProgram(0);

	glDeleteProgram(programId);
	programId = 0;

	GlUtils::checkOpenGLError("ERROR: Could not delete shader program.");
}

void ShaderProgram::addShader(std::string filename, const GLenum &shaderType)
{
	std::string type = "";
	if (shaderType == GL_VERTEX_SHADER)
	{
		type = "VERTEX";
	}
	else if (shaderType == GL_FRAGMENT_SHADER)
	{
		type = "FRAGMENT";
	}

	const std::string file = readFile(filename, type);
	const GLchar* shader = file.c_str();

	GLuint shaderId = glCreateShader(shaderType);

	glShaderSource(shaderId, 1, &shader, 0);
	shaders[type] = shaderId;

	GlUtils::checkOpenGLError("ERROR: Could not add" + filename + "shader.");
}

void ShaderProgram::compileShaders()
{
	for (auto member : shaders)
	{
		glCompileShader(member.second);

		checkCompilationErrors(member.second, member.first);
	}
}

void ShaderProgram::createShaderProgram()
{
	programId = glCreateProgram();

	for (auto member : shaders)
	{
		glAttachShader(programId, member.second);
	}

	GlUtils::checkOpenGLError("ERROR: Could not create shader program.");
}

void ShaderProgram::addAttribute(int index, const char* attribute)
{
	glBindAttribLocation(programId, index, attribute);
	GlUtils::checkOpenGLError("ERROR: Could not add attribute to shaders program.");
}

void ShaderProgram::linkProgram()
{
	glLinkProgram(programId);
	checkProgramLinkageErrors(programId);

	for (auto member : shaders)
	{
		glDetachShader(programId, member.second);

		glDeleteShader(member.second);
	}
	GlUtils::checkOpenGLError("ERROR: Could not detach and delete shaders from shader program.");
}

void ShaderProgram::addUniform(const char* attribute)
{
	uniforms[attribute] = glGetUniformLocation(programId, attribute);
	GlUtils::checkOpenGLError("ERROR: Could not add uniform to shaders program.");
}

void ShaderProgram::addUniformBlock(const char* attribute, const GLuint &UBO_BP)
{
	GLint uboId = glGetUniformBlockIndex(programId, "SharedMatrices");
	glUniformBlockBinding(programId, uboId, UBO_BP);
	GlUtils::checkOpenGLError("ERROR: Could not add uniform block to shaders program.");
}

GLint ShaderProgram::getUniform(const char* attribute)
{
	return uniforms[attribute];
}

bool ShaderProgram::containsUniform(const char* attribute)
{
	if (uniforms.find(attribute) != uniforms.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ShaderProgram::useProgram()
{
	glUseProgram(programId);
}

void ShaderProgram::disableProgram()
{
	glUseProgram(0);
}

std::string ShaderProgram::readFile(const std::string& filename, std::string shaderType)
{
	std::ifstream ifile(filename);
	std::string shader_string;
	if (!ifile.good())
	{
		std::cerr << "ERROR::SHADER::" << shaderType << "::READFILE_FAILED" << std::endl;
	}

	while (ifile.good()) {
		std::string line;
		std::getline(ifile, line);
		shader_string += line + "\n";
	}

	return shader_string;
}

void ShaderProgram::checkCompilationErrors(GLuint shaderId, std::string shaderType)
{
	GLint  success;
	char infoLog[512];

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::" << shaderType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void ShaderProgram::checkProgramLinkageErrors(GLuint progId)
{
	GLint  success;
	char infoLog[512];

	glGetProgramiv(progId, GL_LINK_STATUS, &success);

	if (!success) 
	{
		glGetProgramInfoLog(progId, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKAGE_FAILED\n" << infoLog << std::endl;
	}
}