#include "Picker.h"

#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>

Picker::Picker(Camera* camera, glm::mat4 projectionMatrix)
{
    _camera = camera;
    _projectionMatrix = projectionMatrix;
    _viewMatrix = _camera->getProjectionMatrix();
}

Picker::Picker()
{

}

Picker::~Picker()
{

}

void Picker::update()
{
    _viewMatrix = _camera->getViewMatrix();
    _currentRay = calculateRay();
}

glm::vec3 Picker::calculateRay()
{
    float mouseX = _camera->getMouseCoords().x;
    float mouseY = _camera->getMouseCoords().y;

    //Get normalized device coordinates from viewspace
    glm::vec2 ndCoords = getNDCoords(mouseX,mouseY);

    //Clip coordinates
    glm::vec4 clipCoords(ndCoords.x, ndCoords.y, -1.0f, 1.0f);

    //Eye coordinates
    glm::vec4 eyeCoords = getEyeCoords(clipCoords);

    //World Space
    glm::vec3 worldRay = getWorldCoords(eyeCoords);

    return worldRay;
}

glm::vec2 Picker::getNDCoords(float mouseX, float mouseY)
{
    float x = (2.0f * mouseX) / (_camera->getScreenWidth() - 1);
    float y = (2.0f * mouseY) / (_camera->getScreenHeight() - 1);
    return glm::vec2(x,-y);
}

glm::vec4 Picker::getEyeCoords(glm::vec4 clipCoords)
{
    glm::mat4 invertedProjection = glm::inverse(_projectionMatrix);
    glm::vec4 eyeCoords = clipCoords * invertedProjection;  //may not work
    return glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
}

glm::vec3 Picker::getWorldCoords(glm::vec4 eyeCoords)
{
    glm::mat4 invertedView = glm::inverse(_viewMatrix);
    glm::vec4 rayWorld = eyeCoords * invertedView;
    glm::vec3 mouseRay(rayWorld.x, rayWorld.y, rayWorld.z);
    mouseRay = glm::normalize(mouseRay);
    return mouseRay;
}