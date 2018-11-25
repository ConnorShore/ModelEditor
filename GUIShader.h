#ifndef GUI_SHADER
#define GUI_SHADER

#include "ShaderProgram.h"

#include <GL/glew.h>

class GUIShader : public ShaderProgram
{
public:
    GUIShader();
    ~GUIShader();

    void bindAttributes() override;
	void getUniformLocations() override;

    void loadColor(glm::vec4 color);
    void loadTransformationMatrix(glm::mat4 matrix);

private:
    GLuint _colorLoc, _transformMatrixLoc;
};

#endif