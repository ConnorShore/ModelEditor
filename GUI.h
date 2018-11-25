#ifndef GUI_H
#define GUI_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "GameObject.h"

class GUI : public GameObject
{
public:
    GUI(float x, float y, float sx, float sy, glm::vec4 color);
    GUI();
    ~GUI();

    glm::vec2 getPosition() {return _position;}
    glm::vec2 getScale() {return _scale;}
    glm::vec4 getColor() {return _color;}

    void render();

private:
    GLuint _vaoID, _vboID;
    glm::vec2 _position;
    glm::vec2 _scale;
    glm::vec4 _color;

    void createIDs();

    float _vertices[10] = {
        1,1,
        1,-1,
        -1,-1,
        -1,1,
        1,1
    };
};

#endif