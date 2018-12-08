#ifndef CUBE
#define CUBE

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "Primitive.h"

class Cube : public Primitive {
public:
    Cube(float x, float y, float z, float rx, float ry, float rz, 
         float sx, float sy, float sz, Material& mat);
    Cube(float x, float y, float z, float rx, float ry, float rz, 
         float sx, float sy, float sz);
    Cube();
    ~Cube();

    void render() override;
    void setScale(glm::vec3 newScale)
    {
        scale = newScale;

        boundingBox.aabbMin = glm::vec3(-0.5f*newScale.x*newScale.x, -0.5f*newScale.y*newScale.y, -0.5f*newScale.z*newScale.z);
        boundingBox.aabbMax = glm::vec3(0.5f*newScale.x*newScale.x, 0.5f*newScale.y*newScale.y, 0.5f*newScale.z*newScale.z);
    }

private:
    float verts[144] = {
        //Front
        -0.5, -0.5, -0.5,   0.0, 0.0, -1.0,
        -0.5, 0.5, -0.5,    0.0, 0.0, -1.0,
        0.5, 0.5, -0.5,     0.0, 0.0, -1.0,
        0.5, -0.5, -0.5,    0.0, 0.0, -1.0,

        //Back
        -0.5, -0.5, 0.5,   0.0, 0.0, 1.0,
        0.5, -0.5, 0.5,    0.0, 0.0, 1.0,
        0.5, 0.5, 0.5,     0.0, 0.0, 1.0,
        -0.5, 0.5, 0.5,    0.0, 0.0, 1.0,

        //Top
        0.5, 0.5, -0.5,    0.0, 1.0, 0.0,
        -0.5, 0.5, -0.5,   0.0, 1.0, 0.0,
        -0.5, 0.5, 0.5,    0.0, 1.0, 0.0,
        0.5, 0.5, 0.5,     0.0, 1.0, 0.0,

        //Bottom
        0.5, -0.5, -0.5,    0.0, -1.0, 0.0,
        0.5, -0.5, 0.5,     0.0, -1.0, 0.0,
        -0.5, -0.5, 0.5,    0.0, -1.0, 0.0,
        -0.5, -0.5, -0.5,   0.0, -1.0, 0.0,

        //Right
        0.5, -0.5, 0.5,     1.0, 0.0, 0.0,
        0.5, -0.5, -0.5,    1.0, 0.0, 0.0,
        0.5, 0.5, -0.5,     1.0, 0.0, 0.0,
        0.5, 0.5, 0.5,      1.0, 0.0, 0.0,

        //Left
        -0.5, -0.5, 0.5,    -1.0, 0.0, 0.0,
        -0.5, 0.5, 0.5,     -1.0, 0.0, 0.0,
        -0.5, 0.5, -0.5,    -1.0, 0.0, 0.0,
        -0.5, -0.5, -0.5,   -1.0, 0.0, 0.0
    };
};

#endif