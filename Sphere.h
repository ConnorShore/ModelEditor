#ifndef SPHERE
#define SPHERE

#include "Primitive.h"

class Sphere : public Primitive {
public:
    Sphere(float x, float y, float z, float rx, float ry, float rz, 
         float sx, float sy, float sz, Material& mat);
    Sphere();
    ~Sphere();

    void render() override;

private:
    float faceCount;

    glm::vec3 toSpherical(int th, int ph, glm::vec3 sz);
};


#endif