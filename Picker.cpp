#include "Picker.h"
#include "Physics.h"
#include "Math.h"

#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>

Picker::Picker(Camera* camera)
{
    _camera = camera;
    _projectionMatrix = camera->getProjectionMatrix();
    _viewMatrix = _camera->getProjectionMatrix();
}

Picker::Picker()
{

}

Picker::~Picker()
{

}

glm::vec3 Picker::screenToWorldCoords(float mouseX, float mouseY)
{
    glm::vec2 ndCoords = getNDCoords(mouseX,mouseY);
    glm::vec4 rayStartNDC(ndCoords.x, ndCoords.y, -1.0f, 1.0f);

    // glm::mat4 inverseProjMat = glm::inverse(_camera->getProjectionMatrix());
    // glm::mat4 inverseViewMat = glm::inverse(_camera->getViewMatrix());

    // glm::vec4 rayStartCamera = inverseProjMat * rayStartNDC;
    // rayStartCamera /= rayStartCamera.w;
    
    // glm::vec4 rayStartWorld = inverseViewMat * rayStartCamera;
    // rayStartWorld /= rayStartWorld.w;
    

    // return glm::vec3(rayStartWorld);
    return glm::vec3(rayStartNDC);
}

void Picker::update(std::vector<Primitive*> primitives, TransformController* controller)
{
    _viewMatrix = _camera->getViewMatrix();

    glm::vec3 rayOrigin, rayDirection;
    calculateRay(&rayOrigin, &rayDirection);

    //Check transform controller
    float dist;
    Cube* xControl = controller->getXController();
    glm::mat4 model = Math::createTransformationMatrix(controller->getAxisPosition(TC_AXIS_X), xControl->getRotation(), xControl->getScale());
    bool colliding = Physics::TestIntersectionRayAABB(rayOrigin, rayDirection, xControl->getBoundingBox().aabbMin,
                                        xControl->getBoundingBox().aabbMax, model, dist);
    xControl->isInSelectRange = colliding;

    Cube* yControl = controller->getYController();
    model = Math::createTransformationMatrix(controller->getAxisPosition(TC_AXIS_Y), yControl->getRotation(), yControl->getScale());
    colliding = Physics::TestIntersectionRayAABB(rayOrigin, rayDirection, yControl->getBoundingBox().aabbMin,
                                        yControl->getBoundingBox().aabbMax, model, dist);
    yControl->isInSelectRange = colliding;

    Cube* zControl = controller->getZController();
    model = Math::createTransformationMatrix(controller->getAxisPosition(TC_AXIS_Z), zControl->getRotation(), zControl->getScale());
    colliding = Physics::TestIntersectionRayAABB(rayOrigin, rayDirection, zControl->getBoundingBox().aabbMin,
                                        zControl->getBoundingBox().aabbMax, model, dist);
    zControl->isInSelectRange = colliding;

    //Check objects
    for(Primitive* obj : primitives) {
        glm::mat4 modelMatrix = Math::createTransformationMatrix(obj->getPosition(), obj->getRotation(), obj->getScale());
        obj->setModelMatrix(modelMatrix);
        float intersectDist;
        bool isColliding = Physics::TestIntersectionRayAABB(rayOrigin, rayDirection, obj->getBoundingBox().aabbMin,
                                         obj->getBoundingBox().aabbMax, modelMatrix, intersectDist);
        obj->isInSelectRange = isColliding;
    }
}

void Picker::calculateRay(glm::vec3* rayOrigin, glm::vec3* rayDirection)
{
    float mouseX = _camera->getMouseCoords().x;
    float mouseY = _camera->getMouseCoords().y;

    //Get normalized device coordinates from viewspace
    glm::vec2 ndCoords = getNDCoords(mouseX,mouseY);
    glm::vec4 rayStartNDC(ndCoords.x, ndCoords.y, -1.0f, 1.0f);
    glm::vec4 rayEndNDC(ndCoords.x, ndCoords.y, 1.0f, 1.0f);

    glm::mat4 inverseProjMat = glm::inverse(_camera->getProjectionMatrix());
    glm::mat4 inverseViewMat = glm::inverse(_camera->getViewMatrix());

    glm::vec4 rayStartCamera = inverseProjMat * rayStartNDC;
    rayStartCamera /= rayStartCamera.w;
    
    glm::vec4 rayStartWorld = inverseViewMat * rayStartCamera;
    rayStartWorld /= rayStartWorld.w;

    glm::vec4 rayEndCamera = inverseProjMat * rayEndNDC;
    rayEndCamera /= rayEndCamera.w;

    glm::vec4 rayEndWorld = inverseViewMat * rayEndCamera;
    rayEndWorld /= rayEndWorld.w;

    glm::vec4 rayDirWorld = rayEndWorld - rayStartWorld;
    rayDirWorld = glm::normalize(rayDirWorld);

    *rayOrigin = glm::vec3(rayStartWorld);
    *rayDirection = rayDirWorld;
}

glm::vec2 Picker::getNDCoords(float mouseX, float mouseY)
{
    float x = (2.0f * mouseX) / (_camera->getScreenWidth() - 0.5f);
    float y = (2.0f * mouseY) / (_camera->getScreenHeight() - 0.5f);
    return glm::vec2(x-1,-y+1);
}

glm::vec4 Picker::getEyeCoords(glm::vec4 clipCoords)
{
    glm::mat4 invertedProjection = glm::inverse(_projectionMatrix);
    glm::vec4 eyeCoords = clipCoords * invertedProjection;  //may not work
    return glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
}

glm::vec3 Picker::getWorldCoords(glm::vec4 eyeCoords)
{
    glm::mat4 invertedView = glm::inverse(_viewMatrix);
    glm::vec4 rayWorld = eyeCoords * invertedView;
    glm::vec3 mouseRay(rayWorld.x, rayWorld.y, rayWorld.z);
    mouseRay = glm::normalize(mouseRay);
    return mouseRay;
}