#ifndef STATIC_SHADER_H
#define STATIC_SHADER_H

#include "ShaderProgram.h"

#include <glm/glm.hpp>
#include <string>

class StaticShader : public ShaderProgram
{
public:
	StaticShader();
	~StaticShader();

	void bindAttributes() override;
	void getUniformLocations() override;

	void loadMVPMatrix(glm::mat4 matrix);

private:
	GLuint _mvpMatrix;
};

#endif  // STATIC_SHADER