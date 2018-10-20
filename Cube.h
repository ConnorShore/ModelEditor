#ifndef CUBE
#define CUBE

#include <glm/glm.hpp>
#include <GL/glew.h>

class Cube {
public:
    Cube(float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz);
    Cube();
    ~Cube();

    void render();

    glm::vec3 getPosition() {return _position;}
    glm::vec3 getRotation() {return _rotation;}
    glm::vec3 getScale() {return _scale;}

private:
    glm::vec3 _position, _rotation, _scale;
    GLuint _vaoID, _vboID, _vioID;

    float vertices[56] = {
        -1.0f, -1.0f, 1.0f,        1.0f, 1.0f, 1.0f, 1.0f, //front bottom left  [0]
        1.0f, -1.0f, 1.0f,         1.0f, 1.0f, 0.0f, 1.0f, //front bottom right [1]
        1.0f, 1.0f, 1.0f,          1.0f, 0.0f, 1.0f, 1.0f, //front top right    [2]
        -1.0f, 1.0f, 1.0f,         0.0f, 1.0f, 1.0f, 1.0f, //front top left     [3]

        -1.0f, -1.0f, -1.0f,       1.0f, 0.0f, 0.0f, 1.0f, //back bottom left   [4]
        1.0f, -1.0f, -1.0f,        0.0f, 1.0f, 0.0f, 1.0f, //back bottom right  [5]
        1.0f, 1.0f, -1.0f,         0.0f, 0.0f, 1.0f, 1.0f, //back top right     [6]
        -1.0f, 1.0f, -1.0f,        0.5f, 1.0f, 0.5f, 1.0f //back top left      [7]
    };

    unsigned int indices[24] = {
        0,1,2,3,    //front
        1,5,6,2,    //right
        4,5,6,7,     //back
        4,0,3,7,     //left
        3,2,6,7,     //top
        0,1,5,4     //bottom
    };


    void createIDs();
};

#endif