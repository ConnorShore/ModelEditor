#ifndef DIRECTIONAL_LIGHT
#define DIRECTIONAL_LIGHT

#include "Light.h"
#include <glm/glm.hpp>

class DirectionalLight : public Light {
public:
    DirectionalLight(glm::vec3& direction, glm::vec3& color, float strength);
    ~DirectionalLight();

    glm::vec3 getDirection() {return _direction;}

private:
    glm::vec3 _direction;
};


#endif