#ifndef LIGHT
#define LIGHT

#include "GameObject.h"

#include <glm/glm.hpp>

class Light : public GameObject {
public:
    Light(float x, float y, float z, float r, float g, float b, float a);
    Light();
    ~Light();

    glm::vec3 getPosition() {return _position;}
    glm::vec4 getColor() {return _color;}

private:
    glm::vec3 _position;
    glm::vec4 _color;
};

#endif