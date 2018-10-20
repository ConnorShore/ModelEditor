#include "Cube.h"

#include <cstdio>

Cube::Cube(float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz)
{
    position = glm::vec3(x,y,z);
    rotation = glm::vec3(rx,ry,rz);
    scale = glm::vec3(sx,sy,sz);

    for(unsigned int i = 0; i < 56; i++) {
        vertices.push_back(verts[i]);
        if(i < 24)
            indices.push_back(inds[i]);
    }

    createIDs();
}

Cube::Cube()
{
    position = glm::vec3(0.0f);
    rotation = glm::vec3(0.0f);
    scale = glm::vec3(1.0f);

    createIDs();
}

Cube::~Cube()
{    
}

void Cube::render()
{
    bindVertexArray();
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, 0);
    unbindVertexArray();
}