#ifndef TRANSFORM_CONTROLLER
#define TRANSFORM_CONTROLLER

#include "Cube.h"
#include <glm/glm.hpp>

class TransformController {
public:
    TransformController();
    ~TransformController();

    void render();

private:
    Cube _xControl, _yControl, _zControl;
    glm::vec3 _controlPosition;
};

#endif