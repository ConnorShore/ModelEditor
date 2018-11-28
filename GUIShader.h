#ifndef GUI_SHADER
#define GUI_SHADER

#include "ShaderProgram.h"
#include "Texture.h"

#include <GL/glew.h>

class GUIShader : public ShaderProgram
{
public:
    GUIShader();
    ~GUIShader();

    void bindAttributes() override;
	void getUniformLocations() override;

    void loadTexture();
    void loadTransformationMatrix(glm::mat4 matrix);

private:
    GLuint _textureLoc, _transformMatrixLoc;
};

#endif