#include "GUI.h"

#include <stdio.h>

GUI::GUI(float x, float y, float sx, float sy, glm::vec4 color)
{
    _vaoID = 0;
    _vboID = 0;
    _position = glm::vec2(x,y);
    _scale = glm::vec2(sx, sy);
    _color = color;

    createIDs();
}

GUI::GUI()
{
    _vaoID = 0;
    _vboID = 0;
    _position = glm::vec2(0.0f);
    _scale = glm::vec2(1.0f);
    _color = glm::vec4(1,1,1,1);

    createIDs();
}

GUI::~GUI()
{
}

void GUI::createIDs()
{
    glGenVertexArrays(1, &_vaoID);
    glGenBuffers(1, &_vboID);

    glBindVertexArray(_vaoID);

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glBufferData(GL_ARRAY_BUFFER, 10 * sizeof(float), &_vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GUI::render()
{
    glBindVertexArray(_vaoID);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 10);
    glBindVertexArray(0);
}