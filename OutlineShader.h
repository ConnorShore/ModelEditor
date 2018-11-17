#ifndef OUTLINE_SHADER
#define OUTLINE_SHADER

#include "ShaderProgram.h"

#include <GL/glew.h>

class OutlineShader : public ShaderProgram
{
public:
    OutlineShader();
    ~OutlineShader();

    void bindAttributes() override;
	void getUniformLocations() override;

    void loadIsSelected(bool selected);

    void loadModelMatrix(glm::mat4 matrix);
    void loadProjectionMatrix(glm::mat4 matrix);
    void loadViewMatrix(glm::mat4 matrix);

private:
    GLuint _isSelectedLoc, _modelMatrixLoc, _projectionMatrixLoc, _viewMatrixLoc;
};

#endif