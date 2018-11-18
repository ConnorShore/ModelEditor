#ifndef TRANSFORM_SHADER
#define TRANSFORM_SHADER

#include "ShaderProgram.h"

#include <GL/glew.h>

class TransformShader : public ShaderProgram
{
public:
    TransformShader();
    ~TransformShader();

    void bindAttributes() override;
	void getUniformLocations() override;

    void loadModelMatrix(glm::mat4 matrix);
    void loadProjectionMatrix(glm::mat4 matrix);
    void loadViewMatrix(glm::mat4 matrix);
    void loadAxisID(int id);

private:
    GLuint _modelMatrixLoc, _projectionMatrixLoc, _viewMatrixLoc, _axisIdLoc;
};

#endif