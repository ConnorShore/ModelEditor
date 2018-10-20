#include "Cube.h"

#include <cstdio>
#include "Vertex.h"

Cube::Cube(float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz)
{
    position = glm::vec3(x,y,z);
    rotation = glm::vec3(rx,ry,rz);
    scale = glm::vec3(sx,sy,sz);

    int offset = 0;
    for(unsigned int i = 0; i < 24; i+=3) {
        Vertex vert;
        vert.position.x = verts[i];     vert.position.y = verts[i+1];       vert.position.z = verts[i+2];
        vert.color.r = cols[i+offset];
        vert.color.g = cols[i+1+offset];            
        vert.color.b = cols[i+2+offset];           
        vert.color.a = cols[i+3+offset];
        vertices.push_back(vert);
        indices.push_back(indices[i]);  indices.push_back(indices[i+1]);    indices.push_back(indices[i+2]);
        offset++;
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