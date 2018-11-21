#ifndef PICKER
#define PICKER

#include "Camera.h"
#include "Primitive.h"
#include "TransformController.h"

#include <glm/glm.hpp>

struct Plane {
    glm::vec3 origin;
    glm::vec3 normal;
};

class Picker {
public:
    Picker(Camera* camera);
    Picker();
    ~Picker();

    void update(std::vector<Primitive*> primitives, TransformController* controller);
    bool rayPlaneIntersection(glm::vec3 vectorOrigin, glm::vec3 vectorNormal, Plane plane, glm::vec3* location);
    glm::vec3 screenToWorldCoords(float mouseX, float mouseY);
    void calculateRay(glm::vec3* rayOrigin, glm::vec3* rayDirection, glm::vec2 mouseCoords);
    void calculateRay(glm::vec3* rayOrigin, glm::vec3* rayDirection);

private:;
    glm::mat4 _viewMatrix, _projectionMatrix;

    Camera* _camera;

    glm::vec2 getNDCoords(float mouseX, float mouseY);
    glm::vec4 getEyeCoords(glm::vec4 clipCoords);
    glm::vec3 getWorldCoords(glm::vec4 eyeCoords);
};


#endif