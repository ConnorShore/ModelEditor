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
    _textureLoc = getUniformLocation("tex");
    _transformMatrixLoc = getUniformLocation("transformMatrix");
}

void GUIShader::loadTexture()
{
    loadInt(_textureLoc, 0);
}

void GUIShader::loadTransformationMatrix(glm::mat4 matrix)
{
    loadMatrix4f(_transformMatrixLoc, matrix);
}