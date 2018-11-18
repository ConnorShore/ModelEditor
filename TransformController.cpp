#include "TransformController.h"

#include "Material.h"

TransformController::TransformController()
{
    _controlPosition = glm::vec3(0.0f);

    _xControl = Cube(_controlPosition.x, _controlPosition.y, _controlPosition.z, 0.0f, 0.0f, 0.0f, 1.2f, 0.2f, 0.2f);
    _yControl = Cube(_controlPosition.x, _controlPosition.y, _controlPosition.z, 0.0f, 0.0f, 0.0f, 0.2, 1.2f, 0.2f);
    _zControl = Cube(_controlPosition.x, _controlPosition.y, _controlPosition.z, 0.0f, 0.0f, 0.0f, 0.2f, 0.2f, 1.2f);
}

TransformController::~TransformController()
{
}

void TransformController::render()
{
    
}