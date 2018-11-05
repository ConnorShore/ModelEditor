#include "Light.h"

Light::Light(float x, float y, float z, float r, float g, float b, float intensity)
{
    position = glm::vec3(x,y,z);
    color = glm::vec3(r,g,b);
    intensity = intensity;
}

Light::Light()
{
    position = glm::vec3(0.0f);
    color = glm::vec3(1.0f);
    intensity = 0.5f;
}

Light::~Light()
{
}