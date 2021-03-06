#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cstdio>

#define PI 3.1415926535

void Camera::init(int screenWidth, int screenHeight)
{
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;
    _fov = 70.0f;
    _zNear = 0.2f;
    _zFar = 150.0f;

    _pitch = _yaw = _roll = 0;

    _sensitivity = 0.002f;

    _position = glm::vec3(0.0f, 0.0f, 0.0f);
    _direction = glm::vec3(0.0f, 0.0f, -1.0f);
    _up = glm::vec3(0.0f, 1.0f, 0.0f);

    _projectionMatrix = createProjectionMatrix();
}

void Camera::update()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(_pitch)) * sin(glm::radians(_yaw));
    direction.y = sin(glm::radians(_pitch));
    direction.z = -(cos(glm::radians(_pitch)) * cos(glm::radians(_yaw)));
    _direction = glm::normalize(direction);

    glm::vec3 right;
    right.x = -sin(glm::radians(_yaw) - PI/2.0f);
    right.y = 0.0f;
    right.z = cos(glm::radians(_yaw) - PI/2.0f);
    _right = right;

    _up = glm::normalize(glm::cross(_right, _direction));
}

void Camera::moveForward(float speed)
{
    _position += speed * _direction;
}

void Camera::moveBackward(float speed)
{
    _position -= speed * _direction;
}

void Camera::moveRight(float speed)
{
    _position += speed * _right;
}

void Camera::moveLeft(float speed)
{
    _position -= speed * _right;
}

void Camera::moveUp(float speed)
{
    _position += speed * _up;
}

void Camera::moveDown(float speed)
{
    _position -= speed * _up;
}

void Camera::rotateUp(float speed)
{
    _pitch += speed;
}

void Camera::rotateDown(float speed)
{
    _pitch -= speed;
}

void Camera::rotateLeft(float speed)
{
    _yaw -= speed;
}

void Camera::rotateRight(float speed)
{
    _yaw += speed;
}

glm::vec3 Camera::screenToWorldCoords(float mouseX, float mouseY)
{
    printf("Screen coords: %f, %f\n", mouseX, mouseY);
    glm::vec3 worldCoords;
    glm::mat4 invertedView = glm::inverse(getViewMatrix());
    glm::mat4 invertedProj = glm::inverse(_projectionMatrix);

    glm::vec4 mouseCoords(mouseX, mouseY, 1, 1);
    glm::vec4 result = mouseCoords * invertedProj * invertedView;
    printf("New Coords: %f, %f\n", result.x, result.y);
    return glm::vec3(result);
}

glm::vec2 Camera::screenToNDC()
{
    return glm::vec2(((_mouseCoords.x * 2.0f)/ _screenWidth) - 1.0f, 
                    (1.0f - (_mouseCoords.y * 2.0f)/ _screenHeight));
}

glm::mat4 Camera::createProjectionMatrix()
{
    glm::mat4 projMatrix;
    projMatrix = glm::perspective(glm::radians(_fov), (float)_screenWidth/(float)_screenHeight, _zNear, _zFar);
    _projectionMatrix = projMatrix;
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