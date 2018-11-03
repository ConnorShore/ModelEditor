#ifndef PRIMITIVE
#define PRIMITIVE

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

#include "GameObject.h"
#include "Vertex.h"

class Primitive : public GameObject{
public:
    Primitive();
    virtual ~Primitive();

    glm::vec3 getPosition() {return position;}
    glm::vec3 getRotation() {return rotation;}
    glm::vec3 getScale() {return scale;}
    glm::vec4 getColor() {return color;}

    virtual void render() = 0;

protected:
    glm::vec3 position, rotation, scale;
    glm::vec4 color;
    std::vector<Vertex> vertices;
    
    void createIDs();
    void bindVertexArray();
    void unbindVertexArray();

private:
    GLuint vaoID, vboID;
};

#endif