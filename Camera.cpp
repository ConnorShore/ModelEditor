#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
void Camera::init(int screenWidth, int screenHeight)
{
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;
    _fov = 70.0f;
    _zNear = 1.0f;
    _zFar = 50.0f;

    _position = glm::vec3(0.0f, 0.0f, 0.0f);
    _direction = glm::vec3(0.0f, 0.0f, -1.0f);
    _up = glm::vec3(0.0f, 1.0f, 0.0f);

    _projectionMatrix = createProjectionMatrix();
}

glm::mat4 Camera::createProjectionMatrix()
{
    glm::mat4 projMatrix;
    projMatrix = glm::perspective(glm::radians(_fov), (float)_screenWidth/(float)_screenHeight, _zNear, _zFar);
    return projMatrix;
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(_position, _position + _direction, _up);
}

glm::mat4 Camera::getProjectionMatrix()
{
    return _projectionMatrix;
}