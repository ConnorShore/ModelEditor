#ifndef TEXT_SHADER
#define TEXT_SHADER

#include "ShaderProgram.h"

class TextShader : public ShaderProgram
{
public:
    TextShader();
    ~TextShader();

    void bindAttributes() override;
	void getUniformLocations() override;

    void loadGlyph();
    void loadProjectionMatrix(glm::mat4 matrix);
    void loadTransformationMatrix(glm::mat4 matrix);
    void loadColor(glm::vec3 color);

private:
    GLuint _glyphTexLoc, _projectionMatrixLoc, _colorLoc, _transformMatrixLoc;
};


#endif