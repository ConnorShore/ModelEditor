#include "Cube.h"

#include <cstdio>
#include "Vertex.h"

Cube::Cube(float x, float y, float z, float rx, float ry, float rz, 
           float sx, float sy, float sz, float r, float g, float b, float a)
{
    position = glm::vec3(x,y,z);
    rotation = glm::vec3(rx,ry,rz);
    scale = glm::vec3(sx,sy,sz);
    color = glm::vec4(r,g,b,a);

    for(unsigned int i = 0; i < 144; i += 6) {
        Vertex vert;
        vert.position.x = verts[i];     vert.position.y = verts[i+1];       vert.position.z = verts[i+2];
        vert.normal.x = verts[i+3];     vert.normal.y = verts[i+4];         vert.normal.z = verts[i+5];
        vert.color.r = r;         vert.color.g = g;             vert.color.b = b;     vert.color.a = a;
        // printf("Vertex %d: px: %f, py: %f, pz: %f | nx: %f, ny: %f, nz: %f\n", i,
        //     vert.position.x, vert.position.y, vert.position.z, vert.normal.x, vert.normal.y, vert.normal.z);
        vertices.push_back(vert);
    }

    createIDs();
}

Cube::Cube()
{
    position = glm::vec3(0.0f);
    rotation = glm::vec3(0.0f);
    scale = glm::vec3(1.0f);
    color = glm::vec4(1.0f);

    for(unsigned int i = 0; i < 24; i++) {
        Vertex vert;
        vert.position.x = verts[i];     vert.position.y = verts[i+1];       vert.position.z = verts[i+2];
        vert.normal.x = verts[i+3];     vert.normal.y = verts[i+4];         vert.normal.z = verts[i+5];
        vert.color.r = color.r;         vert.color.g = color.g;             vert.color.b = color.b;     vert.color.a = color.a;
        vertices.push_back(vert);
    }

    createIDs();
}

Cube::~Cube()
{    
}

void Cube::render()
{
    bindVertexArray();
    glDrawArrays(GL_QUADS, 0, 24);
    unbindVertexArray();
}