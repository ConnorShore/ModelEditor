#ifndef RENDERER
#define RENDERER

#include "Primitive.h"
#include "StaticShader.h"
#include "Camera.h"

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

    unsigned int addCube(float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz);

private:
    std::vector<Primitive*> _objects;
    StaticShader* _staticShader;

    unsigned int current_id = 0;
};

#endif