#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3& direction, glm::vec3& col, float strength)
{
    _direction = direction;
    color = col;
    intensity = strength;
}