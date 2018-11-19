#ifndef TRANSFORM_CONTROLLER
#define TRANSFORM_CONTROLLER

#define AXIS_HEIGHT 1.2
#define AXIS_WIDTH 0.2

#define TC_AXIS_X 1
#define TC_AXIS_Y 2
#define TC_AXIS_Z 3

#include "Cube.h"
#include "Camera.h"
#include "TransformShader.h"
#include <glm/glm.hpp>

class TransformController {
public:
    TransformController();
    ~TransformController();

    void render(Camera& camera, TransformShader& shader);

    Cube* getXController() {return _xControl;}
    Cube* getYController() {return _yControl;}
    Cube* getZController() {return _zControl;}

    glm::vec3 getPosition() {return _controlPosition;}
    glm::vec3 getAxisPosition(int id)
    {
        if(id == TC_AXIS_X)
            return _controlPosition + _xControl->getPosition();
        else if(id == TC_AXIS_Y)
            return _controlPosition + _yControl->getPosition();
        else if(id == TC_AXIS_Z)
            return _controlPosition + _zControl->getPosition();
        else
            printf("Axis id: %d does not exist\n", id);
        return glm::vec3(0.0f);
    }
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