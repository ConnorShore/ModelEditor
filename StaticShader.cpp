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
}

void StaticShader::getUniformLocations()
{
	_modelMatrixLoc = getUniformLocation("model");
	_viewMatrixLoc = getUniformLocation("view");
	_projectionMatrixLoc = getUniformLocation("projection");
	_viewPositionLoc = getUniformLocation("viewPosition");

	_lightPositionLoc = getUniformLocation("light.position");
	_lightColorLoc = getUniformLocation("light.color");
	_lightSpecularLoc = getUniformLocation("light.specular");
	_lightIntensityLoc = getUniformLocation("light.intensity");

	_materialAmbientLoc = getUniformLocation("material.ambient");
	_materialDiffuseLoc = getUniformLocation("material.diffuse");
	_materialSpecularLoc = getUniformLocation("material.specular");
	_materialShininessLoc = getUniformLocation("material.shininess");
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

void StaticShader::loadViewPosition(glm::vec3 position)
{
	loadVector3f(_viewPositionLoc, position);
}

void StaticShader::loadMaterial(Material material)
{
	loadVector3f(_materialAmbientLoc, material.ambient); 
	loadVector3f(_materialDiffuseLoc, material.diffuse);
	loadVector3f(_materialSpecularLoc, material.specular);
	loadFloat(_materialShininessLoc, material.shininess);
}

void StaticShader::loadLight(Light light)
{
	loadVector3f(_lightPositionLoc, light.getPosition());
	loadVector3f(_lightColorLoc, light.getColor());
	loadVector3f(_lightSpecularLoc, light.getSpecular());
	loadFloat(_lightIntensityLoc, light.getIntensity());
}