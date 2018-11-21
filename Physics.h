#ifndef PHYSICS
#define PHYSICS

#include <glm/glm.hpp>

struct BoundingBox
{
    glm::vec3 aabbMin;
    glm::vec3 aabbMax;
};

class Physics {
public:
    Physics();
    ~Physics();

    static bool TestIntersectionRayAABB(glm::vec3 rayPos, glm::vec3 rayDirection, glm::vec3 aabbMin, glm::vec3 aabbMax,
                                        glm::mat4 modelMatrix, float& intersectionDistance);

private:

};

#endif