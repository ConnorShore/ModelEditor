#ifndef LIGHT
#define LIGHT

enum LightType
{
    DIRECTIONAL,
    POINT
};

#include "GameObject.h"

#include <glm/glm.hpp>

class Light : public GameObject {
public:
    Light(float x, float y, float z, float r, float g, float b, float intensity);
    Light();
    ~Light();

    glm::vec3 getPosition() {return position;}
    glm::vec3 getColor() {return color;}
    float getIntensity() {return intensity;}
    LightType getLightType() {return lightType;}

    void setIntensity(float intense) {intensity = intense;}

protected:
    glm::vec3 position;
    glm::vec3 color;
    float intensity;
    LightType lightType;
};

#endif