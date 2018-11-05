#include "PointLight.h"

PointLight::PointLight(glm::vec3& pos, glm::vec3& col, float strength, glm::vec3& attenuation)
{
    position = pos;
    color = col;
    intensity = strength;

    _constant = attenuation.x;
    _linear = attenuation.y;
    _quadratic = attenuation.z;
}

PointLight::PointLight()
{
}

PointLight::~PointLight()
{

}