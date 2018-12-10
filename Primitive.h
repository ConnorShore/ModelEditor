#ifndef PRIMITIVE
#define PRIMITIVE

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

#include "GameObject.h"
#include "Vertex.h"
#include "Material.h"
#include "Physics.h"

class Primitive : public GameObject{
public:
    Primitive();
    virtual ~Primitive();

    glm::vec3 getPosition() {return position;}
    glm::vec3 getRotation() {return rotation;}
    glm::vec3 getScale() {return scale;}
    glm::vec3 getBaseScale() {return baseScale;}
    glm::mat4 getModelMatrix() {return modelMatrix;}
    Material getMaterial() {return material;}
    BoundingBox getBoundingBox() {return boundingBox;}

    void setPosition(glm::vec3 pos) {position = pos;}
    void setRotation(glm::vec3 rot) {rotation = rot;}
    void setScale(glm::vec3 newScale) {scale = newScale;}
    void setMaterial(Material& mat) {material = mat;}
    void setModelMatrix(glm::mat4 model) {modelMatrix = model;}
    void setBaseScale(glm::vec3 scale) {baseScale = scale;}
    void setBoundingBox(glm::vec3 aabbMin, glm::vec3 aabbMax)
    {
        boundingBox.aabbMin = aabbMin;
        boundingBox.aabbMax = aabbMax;
    }

    virtual void render() = 0;

    //TODO: Figure out what properties are and if should use here
    bool isInSelectRange = false;
    bool isSelected = false;
    glm::vec3 selectedLocation;
protected:
    glm::vec3 position, rotation, scale;
    glm::mat4 modelMatrix;
    Material material;

    glm::vec3 baseScale;

    BoundingBox boundingBox;
    
    std::vector<Vertex> vertices;
    
    void createIDs();
    void bindVertexArray();
    void unbindVertexArray();

private:
    GLuint vaoID, vboID;
};

#endif