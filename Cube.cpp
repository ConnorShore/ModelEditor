#include "Cube.h"

#include <cstdio>

Cube::Cube(float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz)
{
    _position = glm::vec3(x,y,z);
    _rotation = glm::vec3(rx,ry,rz);
    _scale = glm::vec3(sx,sy,sz);

    createIDs();
}

Cube::Cube()
{
    _position = glm::vec3(0.0f);
    _rotation = glm::vec3(0.0f);
    _scale = glm::vec3(1.0f);

    createIDs();
}

Cube::~Cube()
{    
    glDeleteVertexArrays(1, &_vaoID);
    glDeleteBuffers(1, &_vboID);
    glDeleteBuffers(1, &_vioID);
}

void Cube::render()
{
    glBindVertexArray(_vaoID);
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Cube::createIDs()
{
    glGenVertexArrays(1, &_vaoID);
    glGenBuffers(1, &_vboID);
    glGenBuffers(1, &_vioID);

    glBindVertexArray(_vaoID);

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vioID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}