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

    void deselectAxis();
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
    bool inControl() {return _inControl;}
    bool allAxisSelected() {return _allAxisSelected;}

    void setPosition(glm::vec3 position) {_controlPosition = position;}
    void setVisible(bool visible) {_visible = visible;}
    void setControlling(bool control) {_inControl = control;}
    void setAllAxisSelected(bool selected) {_allAxisSelected = selected;}

    void setRotation(glm::vec3 rotation)
    {
        _xControl->setRotation(rotation);
        _yControl->setRotation(rotation);
        _zControl->setRotation(rotation);
    }

    void moveX(float amount) {_controlPosition.x += amount;}
    void moveY(float amount) {_controlPosition.y += amount;}
    void moveZ(float amount) {_controlPosition.z += amount;}

    float distance;
    bool selectLocUpdated = false;
private:
    Cube* _xControl;
    Cube* _yControl;
    Cube* _zControl;

    glm::vec3 _controlPosition, _controlRotation;
    bool _visible;
    bool _inControl;
    bool _allAxisSelected;
};

#endif