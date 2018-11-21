#include "Physics.h"
#include <stdio.h>

bool Physics::TestIntersectionRayAABB(glm::vec3 rayPos, glm::vec3 rayDirection, glm::vec3 aabbMin, glm::vec3 aabbMax,
                                    glm::mat4 modelMatrix, float& intersectionDistance)
{
    float tMin = 0.0f;
    float tMax = 9999999.9f;

    glm::vec3 bbPosWorldSpace(modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z);
    glm::vec3 delta = bbPosWorldSpace - rayPos;

    //X AXIS
    glm::vec3 xAxis(modelMatrix[0].x, modelMatrix[0].y, modelMatrix[0].z);
    float e = glm::dot(xAxis, delta);
    float f = glm::dot(rayDirection, xAxis);

    if(fabs(f) <- 0.001f) {
        if(-e+aabbMin.x > 0.0f || -e+aabbMax.x < 0.0f)
            return false;
    }

    //check intersections
    float t1 = (e + aabbMin.x)/f;
    float t2 = (e + aabbMax.x)/f;

    //If intersections in wrong order
    if(t1 > t2) {
        float w=t1;
        t1=t2;
        t2=w;
    }

    if(t2 < tMax) tMax = t2;
    if(t1 > tMin) tMin = t1;

    if(tMax < tMin) return false;

    //Y AXIS
    glm::vec3 yAxis(modelMatrix[1].x, modelMatrix[1].y, modelMatrix[1].z);
    e = glm::dot(yAxis, delta);
    f = glm::dot(rayDirection, yAxis);

    if(fabs(f) <- 0.001f) {
        if(-e+aabbMin.y > 0.0f || -e+aabbMax.y < 0.0f)
            return false;
    }

    //check intersections
    t1 = (e + aabbMin.y)/f;
    t2 = (e + aabbMax.y)/f;

    //If intersections in wrong order
    if(t1 > t2) {
        float w=t1;
        t1=t2;
        t2=w;
    }

    if(t2 < tMax) tMax = t2;
    if(t1 > tMin) tMin = t1;

    if(tMax < tMin) return false;

    //Z AXIS
    glm::vec3 zAxis(modelMatrix[2].x, modelMatrix[2].y, modelMatrix[2].z);
    e = glm::dot(zAxis, delta);
    f = glm::dot(rayDirection, zAxis);

    if(fabs(f) <- 0.001f) {
        if(-e+aabbMin.x > 0.0f || -e+aabbMax.x < 0.0f)
            return false;
    }

    //check intersections
    t1 = (e + aabbMin.z)/f;
    t2 = (e + aabbMax.z)/f;

    //If intersections in wrong order
    if(t1 > t2) {
        float w=t1;
        t1=t2;
        t2=w;
    }

    if(t2 < tMax) tMax = t2;
    if(t1 > tMin) tMin = t1;

    if(tMax < tMin) return false;

    intersectionDistance = tMin;
    return true;
}