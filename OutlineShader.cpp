#include "OutlineShader.h"

OutlineShader::OutlineShader()
{

}

OutlineShader::~OutlineShader()
{

}

void OutlineShader::bindAttributes()
{
    bindAttribute(0, "vertexPosition");
}

void OutlineShader::getUniformLocations()
{
    _isSelectedLoc = getUniformLocation("isSelected");
	_modelMatrixLoc = getUniformLocation("model");
	_viewMatrixLoc = getUniformLocation("view");
	_projectionMatrixLoc = getUniformLocation("projection");
}

void OutlineShader::loadIsSelected(bool selected)
{
    loadBool(_isSelectedLoc, selected);
}
void OutlineShader::loadModelMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_modelMatrixLoc, matrix);
}
void OutlineShader::loadViewMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_viewMatrixLoc, matrix);
}
void OutlineShader::loadProjectionMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_projectionMatrixLoc, matrix);
}
