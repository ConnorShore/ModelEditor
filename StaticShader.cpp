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
	bindAttribute(1, "vertexNormal");
	bindAttribute(2, "vertexColor");
}

void StaticShader::getUniformLocations()
{
	_modelMatrixLoc = getUniformLocation("model");
	_viewMatrixLoc = getUniformLocation("view");
	_projectionMatrixLoc = getUniformLocation("projection");
	_lightPositionLoc = getUniformLocation("lightPosition");
	_lightColorLoc = getUniformLocation("lightColor");
}

void StaticShader::loadModelMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_modelMatrixLoc, matrix);
}
void StaticShader::loadViewMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_viewMatrixLoc, matrix);
}
void StaticShader::loadProjectionMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_projectionMatrixLoc, matrix);
}

void StaticShader::loadLightPosition(glm::vec3 position)
{
	loadVector3f(_lightPositionLoc, position);
}

void StaticShader::loadLightColor(glm::vec3 color)
{
	loadVector3f(_lightColorLoc, color);
}