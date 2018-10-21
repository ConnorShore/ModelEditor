#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

#include "Vertex.h"

class GameObject {
public:
    GameObject();
    virtual ~GameObject();

    glm::vec3 getPosition() {return position;}
    glm::vec3 getRotation() {return rotation;}
    glm::vec3 getScale() {return scale;}

    virtual void render() = 0;

protected:
    glm::vec3 position, rotation, scale;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    
    void createIDs();
    void bindVertexArray();
    void unbindVertexArray();

private:
    GLuint vaoID, vboID, vioID;

};

#endif