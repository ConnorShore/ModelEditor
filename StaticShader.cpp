#include "StaticShader.h"

#include "PointLight.h"
#include "DirectionalLight.h"

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

	for(int i =0 ; i < MAX_LIGHTS; i++) {
		std::string pos = std::string("pointLights[") + std::to_string(i) + std::string("].position");
		_pLightPositionLoc[i] = getUniformLocation(pos);

		std::string col = std::string("pointLights[") + std::to_string(i) + std::string("].color");
		_pLightColorLoc[i] = getUniformLocation(col);

		std::string intensity = std::string("pointLights[") + std::to_string(i) + std::string("].intensity");
		_pLightIntensityLoc[i] = getUniformLocation(intensity);

		std::string constant = std::string("pointLights[") + std::to_string(i) + std::string("].constant");
		_pLightConstLoc[i] = getUniformLocation(constant);

		std::string linear = std::string("pointLights[") + std::to_string(i) + std::string("].linear");
		_pLightLinearLoc[i] = getUniformLocation(linear);

		std::string quad = std::string("pointLights[") + std::to_string(i) + std::string("].quadratic");
		_pLightQuadLoc[i] = getUniformLocation(quad);
	}

	_dLightDirectionLoc = getUniformLocation("directionLight.direction");
	_dLightColorLoc = getUniformLocation("directionLight.color");
	_dLightIntensityLoc = getUniformLocation("directionLight.intensity");

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

void StaticShader::loadLights(std::vector<Light*> lights)
{
	//Direcitonal Light
	bool foundDirectionLight = false;
	for(unsigned int i = 0; i < lights.size(); i++) {
		if(DirectionalLight* light = static_cast<DirectionalLight*>(lights[i])) {
			foundDirectionLight = true;
			loadVector3f(_dLightDirectionLoc, light->getDirection());
			loadVector3f(_dLightColorLoc, light->getColor());
			loadFloat(_dLightIntensityLoc, light->getIntensity());
		}
	}

	if(!foundDirectionLight) {
		loadVector3f(_dLightDirectionLoc, glm::vec3(0.0f));
		loadVector3f(_dLightColorLoc, glm::vec3(0.0f));
		loadFloat(_dLightIntensityLoc, 0.0f);
	}

	//Point Lights
	unsigned int count = 0;
	for(unsigned int i = 0; i < MAX_LIGHTS; i++) {
		if(count < lights.size()) {
			if(PointLight* light = static_cast<PointLight*>(lights[i])) {
				count++;
				loadVector3f(_pLightPositionLoc[i], light->getPosition());
				loadVector3f(_pLightColorLoc[i], light->getColor());
				loadFloat(_pLightIntensityLoc[i], light->getIntensity());
				loadFloat(_pLightConstLoc[i], light->getConstant());
				loadFloat(_pLightLinearLoc[i], light->getLinear());
				loadFloat(_pLightQuadLoc[i], light->getQuadratic());
			}
		} 
		else {
			loadVector3f(_pLightPositionLoc[i], glm::vec3(0.0f));
			loadVector3f(_pLightColorLoc[i], glm::vec3(0.0f));
			loadFloat(_pLightIntensityLoc[i], 1.0f);
			loadFloat(_pLightConstLoc[i], 1.0f);
			loadFloat(_pLightLinearLoc[i], 0.0f);
			loadFloat(_pLightQuadLoc[i], 0.0f);
		}
	}
}