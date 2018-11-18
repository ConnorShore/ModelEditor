#include "TransformShader.h"

TransformShader::TransformShader()
{

}

TransformShader::~TransformShader()
{

}

void TransformShader::bindAttributes()
{
    bindAttribute(0, "vertexPosition");
}

void TransformShader::getUniformLocations()
{
	_axisIdLoc = getUniformLocation("axisID");
	_modelMatrixLoc = getUniformLocation("model");
	_viewMatrixLoc = getUniformLocation("view");
	_projectionMatrixLoc = getUniformLocation("projection");
}

void TransformShader::loadAxisID(int id)
{
	loadInt(_axisIdLoc, id);
}
void TransformShader::loadModelMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_modelMatrixLoc, matrix);
}
void TransformShader::loadViewMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_viewMatrixLoc, matrix);
}
void TransformShader::loadProjectionMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_projectionMatrixLoc, matrix);
}
