#include "Light.h"

Light::Light(float x, float y, float z, float r, float g, float b/*, float specX, float specY, float specZ*/)
{
    _position = glm::vec3(x,y,z);
    _color = glm::vec3(r,g,b);
    //_specular = glm::vec3(specX, specY, specZ);
}

Light::Light()
{
    _position = glm::vec3(0.0f);
    _color = glm::vec3(1.0f);
    //_specular = glm::vec3(1.0f);
}

Light::~Light()
{
}