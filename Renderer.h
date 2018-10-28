#ifndef RENDERER
#define RENDERER

#include "Primitive.h"
#include "StaticShader.h"
#include "Camera.h"
#include "Light.h"

#include <SDL2/SDL.h>
#include <vector>

class Renderer {
public:
    Renderer();
    ~Renderer();

    void init(StaticShader* shader);

    void beginRender();
    void renderObjects(Camera& camera);
    void endRender(SDL_Window* window);
    GameObject* getGameObject(unsigned int id);

    unsigned int addCube(float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz);
    unsigned int addLight(float x, float y, float z, float r, float g, float b, float a);

private:
    std::vector<Primitive*> _objects;
    std::vector<Light*> _lights;
    StaticShader* _staticShader;

    unsigned int currentID = 0;
};

#endif