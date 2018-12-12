#include "LightOverlay.h"

#include <GL/glew.h>
#include "Loader.h"

LightOverlay::LightOverlay(Light* parent)
{
    _position = parent->getPosition();
    _scale = glm::vec3(0.5f,0.5f,0.0f);
    _normal = glm::vec3(0.0f, 0.0f, -1.0f);
    _texture = Loader::loadPNG("Textures/addCube.png");

    glGenVertexArrays(1, &_vaoID);
    glGenBuffers(1, &_vboID);

    glBindVertexArray(_vaoID);
    printf("Binding buffer\n");

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeof(_vertices), &_vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    printf("Created\n");
}

LightOverlay::~LightOverlay()
{
}

void LightOverlay::update(Camera* camera)
{
    _position = _parent->getPosition();
    printf("Parent pos: %f, %f, %f\n", _parent->getPosition().x, _parent->getPosition().y, _parent->getPosition().z);
    printf("Position: %f,%f,%f\n", _position.x, _position.y, _position.z);
    _normal = camera->getViewDirection();
}

void LightOverlay::render()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture.id);

    glBindVertexArray(_vaoID);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
}