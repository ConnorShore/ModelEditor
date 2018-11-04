#include "StaticShader.h"

#include "PointLight.h"

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
		printf("POS: %s\n", pos.c_str());
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
	unsigned int count = 0;
	for(unsigned int i = 0; i < MAX_LIGHTS; i++) {
		printf("Loading light[%d]\n", i);
		if(count < lights.size()) {
			if(PointLight* light = static_cast<PointLight*>(lights[i])) {
				count++;
				printf("Color: %f,%f,%f\n", light->getColor().x, light->getColor().y, light->getColor().z);
				loadVector3f(_pLightPositionLoc[i], light->getPosition());
				loadVector3f(_pLightColorLoc[i], light->getColor());
				loadFloat(_pLightIntensityLoc[i], light->getIntensity());
				loadFloat(_pLightConstLoc[i], light->getConstant());
				loadFloat(_pLightLinearLoc[i], light->getLinear());
				loadFloat(_pLightQuadLoc[i], light->getQuadratic());
			}
		} 
		else {
			printf("Loading default light\n");
			loadVector3f(_pLightPositionLoc[i], glm::vec3(0.0f));
			loadVector3f(_pLightColorLoc[i], glm::vec3(0.0f));
			loadFloat(_pLightIntensityLoc[i], 1.0f);
			loadFloat(_pLightConstLoc[i], 1.0f);
			loadFloat(_pLightLinearLoc[i], 0.0f);
			loadFloat(_pLightQuadLoc[i], 0.0f);
		}
		printf("Loaded light[%d]\n", i);
	}
}