#include "StaticShader.h"



StaticShader::StaticShader()
{
	
}

StaticShader::~StaticShader()
{
}

void StaticShader::bindAttributes()
{
	bindAttribute(0, "vertexPosition");
	bindAttribute(1, "vertexColor");
}

void StaticShader::getUniformLocations()
{
	_mvpMatrix = getUniformLocation("mvp");
}

void StaticShader::loadMVPMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_mvpMatrix, matrix);
}