#ifndef MAIN_EDITOR_H
#define MAIN_EDITOR_H

#define GL_GLEXT_PROTOTYPES

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <vector>

#include "StaticShader.h"
#include "Camera.h"
#include "Renderer.h"
#include "Cube.h"

class MainEditor
{
public:
    MainEditor() {}

    void run();

private:

    SDL_Window* window;
    StaticShader staticShader;
    Camera camera;
    Renderer renderer;

    int screenWidth = 1600;
    int screenHeight = 900;
    bool isRunning = false;

    void init();
    void update();
    void render();
    void gameLoop();
    void cleanUp();
};

#endif // MAIN_EDITOR