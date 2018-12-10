#include "TransformController.h"
#include "Math.h"

TransformController::TransformController()
{
    _controlPosition = glm::vec3(0.0f);
    _visible = false;

    _xControl = new Cube(AXIS_HEIGHT/2 - AXIS_WIDTH/2, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, AXIS_HEIGHT, AXIS_WIDTH, AXIS_WIDTH);
    _yControl = new Cube(0.0f, AXIS_HEIGHT/2 - AXIS_WIDTH/2, 0.0f, 0.0f, 0.0f, 0.0f, AXIS_WIDTH, AXIS_HEIGHT, AXIS_WIDTH);
    _zControl = new Cube(0.0f, 0.0f, AXIS_HEIGHT/2 - AXIS_WIDTH/2, 0.0f, 0.0f, 0.0f, AXIS_WIDTH, AXIS_WIDTH, AXIS_HEIGHT);
}

TransformController::~TransformController()
{
}

void TransformController::deselectAxis()
{
    _xControl->isSelected = false;
    _yControl->isSelected = false;
    _zControl->isSelected = false;
}

void TransformController::render(Camera& camera, TransformShader& shader)
{
    if(_visible == false)
        return;

    shader.start();
    shader.getUniformLocations();
    shader.loadProjectionMatrix(camera.createProjectionMatrix());
    shader.loadViewMatrix(camera.getViewMatrix());

    //X Axis Controller
    glm::mat4 model = Math::createTransformationMatrix(_controlPosition, _xControl->getRotation(), _xControl->getScale());
    // model *= Math::createTransformationMatrix(_controlPosition + _xControl->getPosition(), glm::vec3(0.0f), glm::vec3(0.0f));
    model = glm::translate(model, _xControl->getPosition());
    // glm::vec3 aabbMin = glm::vec3(model[3]);
    // glm::vec3 aabbMax = glm::vec3(model[3]);
    // aabbMin -= _xControl->getScale()/2.0f;
    // aabbMax += _xControl->getScale()/2.0f;
    // _xControl->setBoundingBox(aabbMin, aabbMax);
    shader.loadModelMatrix(model);
    shader.loadAxisID(0);
    shader.loadSelected(_xControl->isSelected);
    _xControl->render();

    //Y Axis Controller
    model = Math::createTransformationMatrix(_controlPosition, _yControl->getRotation(), _yControl->getScale());
    model = glm::translate(model, _yControl->getPosition());
    // aabbMin = glm::vec3(model[3]);
    // aabbMax = glm::vec3(model[3]);
    // aabbMin -= _yControl->getScale()/2.0f;
    // aabbMax += _yControl->getScale()/2.0f;
    // _yControl->setBoundingBox(aabbMin, aabbMax);
    shader.loadModelMatrix(model);
    shader.loadAxisID(1);
    shader.loadSelected(_yControl->isSelected);
    _yControl->render();

    //Z Axis Controller
    //newer
    model = Math::createTransformationMatrix(_controlPosition, _zControl->getRotation(), _zControl->getScale());
    model = glm::translate(model, _zControl->getPosition());
    // aabbMin = glm::vec3(model[3]);
    // aabbMax = glm::vec3(model[3]);
    // aabbMin -= _zControl->getScale()/2.0f;
    // aabbMax += _zControl->getScale()/2.0f;
    // _zControl->setBoundingBox(aabbMin, aabbMax);

    //old
    // model = Math::createTransformationMatrix(_controlPosition + _zControl->getPosition(), _zControl->getRotation(), _zControl->getScale());
    shader.loadModelMatrix(model);
    shader.loadAxisID(2);
    shader.loadSelected(_zControl->isSelected);
    _zControl->render();

    shader.stop();
}