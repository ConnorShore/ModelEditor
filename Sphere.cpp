#include "Sphere.h"
#include <stdio.h>

#define Cos(th) cos(3.1415926f/180*(th))
#define Sin(th) sin(3.1415926f/180*(th))

glm::vec3 Sphere::toSpherical(int th, int ph, glm::vec3 sz)
{
    glm::vec3 ret(Sin(th)*Cos(ph) * sz.x, Sin(ph)*sz.y, Cos(th)*Cos(ph)*sz.z);
    return ret;
}

Sphere::Sphere(float x, float y, float z, float rx, float ry, float rz, 
         float sx, float sy, float sz, Material& mat) {
    faceCount = 0;
    position = glm::vec3(x,y,z);
    rotation = glm::vec3(rx,ry,rz);
    scale = glm::vec3(sx,sy,sz);
    material = mat;

    int d = 10;
    for(int ph = -90; ph < 90; ph += d) {

        for(unsigned int th = 0; th <= 360; th+=d) {
            Vertex vert;
            glm::vec3 pos = toSpherical(th,ph,scale);
            vert.position.x = pos.x;
            vert.position.y = pos.y;
            vert.position.z = pos.z;
            vert.normal.x = pos.x;
            vert.normal.y = pos.y;
            vert.normal.z = pos.z;
            vertices.push_back(vert);

            Vertex vert2;
            glm::vec3 pos2 = toSpherical(th,ph+d,scale);
            vert2.position.x = pos2.x;
            vert2.position.y = pos2.y;
            vert2.position.z = pos2.z;
            vert2.normal.x = pos2.x;
            vert2.normal.y = pos2.y;
            vert2.normal.z = pos2.z;
            vertices.push_back(vert2);
            
            faceCount += 2;
        }
    }

    createIDs();
}

Sphere::~Sphere()
{
}

void Sphere::render()
{
    printf("rendering sphere\n");
    bindVertexArray();
    glDrawArrays(GL_QUAD_STRIP, 0, (int)faceCount);
    unbindVertexArray();
}