#ifndef STATIC_SHADER_H
#define STATIC_SHADER_H

#include "ShaderProgram.h"
#include "Material.h"

#include <glm/glm.hpp>
#include <string>

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
	void loadLightPosition(glm::vec3 position);
	void loadLightColor(glm::vec3 color);
	void loadMaterial(Material material);

private:
	GLuint _modelMatrixLoc, _viewMatrixLoc, _projectionMatrixLoc;
	GLuint _viewPositionLoc;
	GLuint _materialAmbientLoc, _materialDiffuseLoc, _materialSpecularLoc, _materialShininessLoc;
	GLuint _lightPositionLoc, _lightColorLoc;
};

#endif  // STATIC_SHADER