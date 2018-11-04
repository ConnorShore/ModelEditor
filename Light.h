#ifndef LIGHT
#define LIGHT

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

protected:
    glm::vec3 position;
    glm::vec3 color;
    float intensity;
};

#endif