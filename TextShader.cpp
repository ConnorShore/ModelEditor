#include "TextShader.h"

TextShader::TextShader()
{
}

TextShader::~TextShader()
{
}

void TextShader::bindAttributes()
{
    bindAttribute(0, "vertex");
}

void TextShader::getUniformLocations()
{
    _projectionMatrixLoc = getUniformLocation("projectionMatrix");
    _colorLoc = getUniformLocation("glyphColor");
    _glyphTexLoc = getUniformLocation("text");
}

void TextShader::loadGlyph()
{
    loadInt(_glyphTexLoc, 0);
}

void TextShader::loadProjectionMatrix(glm::mat4 matrix)
{
    loadMatrix4f(_projectionMatrixLoc, matrix);
}

void TextShader::loadColor(glm::vec3 color)
{
    loadVector3f(_colorLoc, color);
}