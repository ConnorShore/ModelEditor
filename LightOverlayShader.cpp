#include "LightOverlayShader.h"

LightOverlayShader::LightOverlayShader()
{

}

LightOverlayShader::~LightOverlayShader()
{

}

void LightOverlayShader::bindAttributes()
{
    bindAttribute(0, "vertexPosition");
	bindAttribute(1, "vertexUV");
}

void LightOverlayShader::getUniformLocations()
{
	_modelMatrixLoc = getUniformLocation("model");
	_viewMatrixLoc = getUniformLocation("view");
	_projectionMatrixLoc = getUniformLocation("projection");
    _textureLoc = getUniformLocation("logo");
}

void LightOverlayShader::loadModelMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_modelMatrixLoc, matrix);
}

void LightOverlayShader::loadViewMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_viewMatrixLoc, matrix);
}

void LightOverlayShader::loadProjectionMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_projectionMatrixLoc, matrix);
}

void LightOverlayShader::loadTexture()
{
    loadInt(0, _textureLoc);
}
