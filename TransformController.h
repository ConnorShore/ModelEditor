#ifndef TRANSFORM_CONTROLLER
#define TRANSFORM_CONTROLLER

#define AXIS_HEIGHT 1.2
#define AXIS_WIDTH 0.2

#include "Cube.h"
#include "Camera.h"
#include "TransformShader.h"
#include <glm/glm.hpp>

class TransformController {
public:
    TransformController();
    ~TransformController();

    void render(Camera& camera, TransformShader& shader);

    glm::vec3 getPosition() {return _controlPosition;}
    bool isVisible() {return _visible;}

    void setPosition(glm::vec3 position) {_controlPosition = position;}
    void setVisible(bool visible) {_visible = visible;}

private:
    Cube* _xControl;
    Cube* _yControl;
    Cube* _zControl;

    glm::vec3 _controlPosition;
    bool _visible;
};

#endif