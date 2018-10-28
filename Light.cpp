#include "Light.h"

Light::Light(float x, float y, float z, float r, float g, float b, float a)
{
    _position = glm::vec3(x,y,z);
    _color = glm::vec4(r,g,b,a);
}

Light::Light()
{
    _position = glm::vec3(0.0f);
    _color = glm::vec4(255);
}

Light::~Light()
{
}