#ifndef PICKER
#define PICKER

#include "Camera.h"
#include "Primitive.h"

#include <glm/glm.hpp>

class Picker {
public:
    Picker(Camera* camera, glm::mat4 projectionMatrix);
    Picker();
    ~Picker();

    void update(std::vector<Primitive*> primitives);

    glm::vec3 getCurrentRay() {return _currentRay;}

private:
    glm::vec3 _currentRay;
    glm::mat4 _viewMatrix, _projectionMatrix;

    Camera* _camera;

    void calculateRay(glm::vec3* rayOrigin, glm::vec3* rayDirection);
    glm::vec2 getNDCoords(float mouseX, float mouseY);
    glm::vec4 getEyeCoords(glm::vec4 clipCoords);
    glm::vec3 getWorldCoords(glm::vec4 eyeCoords);
};


#endif