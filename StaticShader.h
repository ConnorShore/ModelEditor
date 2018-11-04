#ifndef STATIC_SHADER_H
#define STATIC_SHADER_H

#include "ShaderProgram.h"
#include "Material.h"
#include "Light.h"

#include <glm/glm.hpp>
#include <string>
#include <vector>

class StaticShader : public ShaderProgram
{
public:
	StaticShader();
	~StaticShader();

	void bindAttributes() override;
	void getUniformLocations() override;

	void loadModelMatrix(glm::mat4 matrix);
	void loadViewMatrix(glm::mat4 matrix);
	void loadProjectionMatrix(glm::mat4 matrix);
	void loadViewPosition(glm::vec3 position);
	void loadMaterial(Material material);
	void loadLights(std::vector<Light*> lights);

	static const int MAX_LIGHTS = 4;
private:
	GLuint _modelMatrixLoc, _viewMatrixLoc, _projectionMatrixLoc;
	GLuint _viewPositionLoc;
	GLuint _materialAmbientLoc, _materialDiffuseLoc, _materialSpecularLoc, _materialShininessLoc;

	GLuint _pLightPositionLoc[MAX_LIGHTS], _pLightColorLoc[MAX_LIGHTS], _pLightIntensityLoc[MAX_LIGHTS];
	GLuint _pLightConstLoc[MAX_LIGHTS], _pLightLinearLoc[MAX_LIGHTS], _pLightQuadLoc[MAX_LIGHTS];
};

#endif  // STATIC_SHADER