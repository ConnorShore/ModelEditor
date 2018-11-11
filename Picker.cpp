#include "Picker.h"
#include "Physics.h"
#include "Math.h"

#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>

Picker::Picker(Camera* camera, glm::mat4 projectionMatrix)
{
    _camera = camera;
    _projectionMatrix = projectionMatrix;
    _viewMatrix = _camera->getProjectionMatrix();
}

Picker::Picker()
{

}

Picker::~Picker()
{

}

void Picker::update(std::vector<Primitive*> primitives)
{
    _viewMatrix = _camera->getViewMatrix();

    glm::vec3 rayOrigin, rayDirection;
    calculateRay(&rayOrigin, &rayDirection);

    for(Primitive* obj : primitives) {
        glm::mat4 modelMatrix = Math::createTransformationMatrix(obj->getPosition(), obj->getRotation(), obj->getScale());
        obj->setModelMatrix(modelMatrix);
        float intersectDist;
        printf("GameObject: %d\n", obj->getID());
        bool isColliding = Physics::TestIntersectionRayAABB(rayOrigin, rayDirection, obj->getBoundingBox().aabbMin,
                                         obj->getBoundingBox().aabbMax, modelMatrix, intersectDist);
        // printf("Colliding with obj: %d\t\tIntersect Distance: %f\n", obj->getID(), intersectDist);
        // printf("Ray origin: %f,%f,%f\n", rayOrigin.x, rayOrigin.y, rayOrigin.z);
        // printf("Ray direct: %f,%f,%f\n", rayDirection.x, rayDirection.y, rayDirection.z);

        obj->isColliding = isColliding;
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
    printf("Ray Start NDC: %f,%f,%f\n", rayStartNDC.x, rayStartNDC.y, rayStartNDC.z);

    glm::mat4 inverseProjMat = glm::inverse(_camera->getProjectionMatrix());
    glm::mat4 inverseViewMat = glm::inverse(_camera->getViewMatrix());

    glm::vec4 rayStartCamera = inverseProjMat * rayStartNDC;// * rayStartCamera/rayStartCamera.w;
    rayStartCamera /= rayStartCamera.w;
    printf("Ray Start Camera: %f,%f,%f\n", rayStartCamera.x, rayStartCamera.y, rayStartCamera.z);
    
    glm::vec4 rayStartWorld = inverseViewMat * rayStartCamera;// * rayStartWorld/rayStartWorld.w;
    rayStartWorld /= rayStartWorld.w;

    glm::vec4 rayEndCamera = inverseProjMat * rayEndNDC;// * rayEndCamera/rayEndCamera.w;
    rayEndCamera /= rayEndCamera.w;
    printf("Ray End Camera: %f,%f,%f\n", rayEndCamera.x, rayEndCamera.y, rayEndCamera.z);

    glm::vec4 rayEndWorld = inverseViewMat * rayEndCamera;// * rayEndWorld/rayEndWorld.w;
    rayEndWorld /= rayEndWorld.w;


    glm::vec4 rayDirWorld = rayEndWorld - rayStartWorld;
    rayDirWorld = glm::normalize(rayDirWorld);
    // printf("Ray origin world.z:%f\n", rayStartWorld.z);
    // printf("Ray dir world.z:%f\n", rayDirWorld.z);

    *rayOrigin = glm::vec3(rayStartWorld);
    *rayDirection = rayDirWorld;
    // //Clip coordinates
    // glm::vec4 clipCoords(ndCoords.x, ndCoords.y, -1.0f, 1.0f);

    // //Eye coordinates
    // glm::vec4 eyeCoords = getEyeCoords(clipCoords);

    // //World Space
    // glm::vec3 worldRay = getWorldCoords(eyeCoords);

    // return worldRay;
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