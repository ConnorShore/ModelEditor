#include "GUIShader.h"

GUIShader::GUIShader()
{

}

GUIShader::~GUIShader()
{

}

void GUIShader::bindAttributes()
{
    bindAttribute(0, "vertexPosition");
}

void GUIShader::getUniformLocations()
{
    _colorLoc = getUniformLocation("color");
    _transformMatrixLoc = getUniformLocation("transformMatrix");
}

void GUIShader::loadColor(glm::vec4 color)
{
    loadVector4f(_colorLoc, color);
}

void GUIShader::loadTransformationMatrix(glm::mat4 matrix)
{
    loadMatrix4f(_transformMatrixLoc, matrix);
}