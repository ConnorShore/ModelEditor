#ifndef LIGHT_OVERLAY_SHADER
#define LIGHT_OVERLAY_SHADER

#include "ShaderProgram.h"

#include <GL/glew.h>

class LightOverlayShader : public ShaderProgram
{
public:
    LightOverlayShader();
    ~LightOverlayShader();

    void bindAttributes() override;
	void getUniformLocations() override;

    void loadModelMatrix(glm::mat4 matrix);
    void loadProjectionMatrix(glm::mat4 matrix);
    void loadViewMatrix(glm::mat4 matrix);
    void loadTexture();

private:
    GLuint _modelMatrixLoc, _projectionMatrixLoc, _viewMatrixLoc, _textureLoc;
};

#endif