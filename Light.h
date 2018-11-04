#ifndef LIGHT
#define LIGHT

#include "GameObject.h"

#include <glm/glm.hpp>

class Light : public GameObject {
public:
    Light(float x, float y, float z, float r, float g, float b/*, float specX, float specY, float specZ*/);
    Light();
    ~Light();

    glm::vec3 getPosition() {return _position;}
    glm::vec3 getColor() {return _color;}
    //glm::vec3 getSpecular() {return _specular;}

private:
    glm::vec3 _position;
    glm::vec3 _color;
    //glm::vec3 _specular;
};

#endif