#include "ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <fstream>

GLuint ShaderProgram::loadShader(const std::string& file, GLuint type)
{
	//read shader from file
	std::string input;
	std::ifstream shaderStream(file, std::ios::in);
	if (shaderStream.is_open()) {
		std::string line;
		while (std::getline(shaderStream, line))
			input += "\n" + line;
		shaderStream.close();
	}

	GLuint shaderID = glCreateShader(type);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	//Compile shader
	if (type == GL_VERTEX_SHADER)
		printf("Compiling vertex shader\n");
	else if (type == GL_FRAGMENT_SHADER)
		printf("Compiling fragment shader\n");

	const char* shaderPointer = input.c_str();

	glShaderSource(shaderID, 1, &shaderPointer, NULL);
	glCompileShader(shaderID);

	//Check shader
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(shaderID, InfoLogLength, NULL, ShaderErrorMessage.data());
	fprintf(stdout, "%s\n", ShaderErrorMessage.data());

	return shaderID;
}

void ShaderProgram::init(const std::string& vertexFile, const std::string& fragmentFile)
{
	VERTEX_FILE = vertexFile;
	FRAGMENT_FILE = fragmentFile;

	_vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
	_fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	_programID = glCreateProgram();

	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);
	glLinkProgram(_programID);
	glValidateProgram(_programID);

	//Check program
	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetProgramiv(_programID, GL_LINK_STATUS, &Result);
	glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage(InfoLogLength, int(1));
	glGetProgramInfoLog(_programID, InfoLogLength, NULL, ProgramErrorMessage.data());
	fprintf(stdout, "%s\n", ProgramErrorMessage.data());
}

void ShaderProgram::start()
{
	glUseProgram(_programID);
}

void ShaderProgram::stop()
{
	glUseProgram(0);
}

void ShaderProgram::cleanUp()
{
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
	glDeleteProgram(_programID);
}

void ShaderProgram::bindAttribute(int attrib, std::string name)
{
	glBindAttribLocation(_programID, attrib, name.c_str());
}

GLuint ShaderProgram::getUniformLocation(std::string name)
{
	return glGetUniformLocation(_programID, name.c_str());
}

void ShaderProgram::loadVector3f(int location, glm::vec3 vec)
{
	glUniform3f(location, vec.x, vec.y, vec.z);
}

void ShaderProgram::loadVector4f(int location, glm::vec4 vec)
{
	glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}

void ShaderProgram::loadMatrix4f(int location, glm::mat4 matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
