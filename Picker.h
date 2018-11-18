#ifndef PICKER
#define PICKER

#include "Camera.h"
#include "Primitive.h"
#include "TransformController.h"

#include <glm/glm.hpp>

class Picker {
public:
    Picker(Camera* camera);
    Picker();
    ~Picker();

    void update(std::vector<Primitive*> primitives, TransformControler& tControl);

private:;
    glm::mat4 _viewMatrix, _projectionMatrix;

    Camera* _camera;

    void calculateRay(glm::vec3* rayOrigin, glm::vec3* rayDirection);
    glm::vec2 getNDCoords(float mouseX, float mouseY);
    glm::vec4 getEyeCoords(glm::vec4 clipCoords);
    glm::vec3 getWorldCoords(glm::vec4 eyeCoords);
};


#endif