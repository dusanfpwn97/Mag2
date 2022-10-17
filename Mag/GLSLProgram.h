#pragma once
#include <string>
#include <GL/glew.h>

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string &vertexShaderFilepath, const std::string &fragmentShaderFilepath);

	void linkShaders();

	void addAttribute(const std::string& attributeName);;

	void use();
	void unUse();

	GLint getUniformLocation(const std::string& uniformName);
private:
	int _numAttributes;
	GLint _programID;

	GLint _vertexShaderID;
	GLint _fragmentShaderID;

	void compileShader(const std::string& filepath, GLint id);
};

